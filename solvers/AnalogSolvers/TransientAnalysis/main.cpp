#define _USE_MATH_DEFINES
#include <cmath>
#include <ctime>

#include <iostream>
#include <fstream>
#include <string>
#include "Eigen/Dense"

#include "elementsloader.h"

#define FIXED_STEP
#define WITHOUT_PREDICTION
// #define DEBUG

void predict_initial(Eigen::VectorXd &values, const Eigen::VectorXd &prev_values, const Eigen::VectorXd &prev_prev_values);
int check_error(const Eigen::VectorXd &correction, double max_error, int iter, int max_iter); // 0 - continue, 1 - done, -1 - max iterations reached
int check_accuracy(const Eigen::VectorXd &values, const Eigen::VectorXd &prev_values, const Eigen::VectorXd &prev_prev_values, double acr_min, double acr_max, double cur_dt); // 0 - dt = dt, -1 - dt = dt/2, 1 - dt = dt*2
void write_result(std::ofstream &f_out, Eigen::VectorXd &values, double t);

int main(int argc, char *argv[])
{
    if (argc < 3) {
        fprintf(stderr, "Arguments format: <netlist file> <out csv file>\n");
        return 1;
    }

    std::string netlist_file_path(argv[1]);
    std::string out_csv_file_path(argv[2]);

    ElementsLoader elements_loader;
    elements_loader.load(netlist_file_path.c_str());
    SolverSettings solver_settings = elements_loader.getSolverSettings();

    #ifdef DEBUG
        std::cout << elements_loader.toString().toStdString();
    #endif

    const double model_t = solver_settings.analysis_time;
    #ifdef FIXED_STEP
        const double start_dt = solver_settings.start_time_step;
    #else
        const double start_dt = solver_settings.start_time_step;
    #endif
    const double acr_min = 1e-1;
    const double acr_max = 1e-3;
    const double max_error = solver_settings.max_correction_error;
    const double max_iter = solver_settings.max_newtons_iterations;

    Eigen::MatrixXd jacobian, jacobian_cut;
    Eigen::VectorXd residual, residual_cut;
    Eigen::VectorXd correction, correction_cut;
    Eigen::VectorXd values = Eigen::VectorXd::Zero(elements_loader.getMatrixSize());
    Eigen::VectorXd prev_values = Eigen::VectorXd::Zero(elements_loader.getMatrixSize());
    Eigen::VectorXd prev_prev_values = Eigen::VectorXd::Zero(elements_loader.getMatrixSize());

    double cur_dt = start_dt;
    double t = 0;
    TimeInfo time_info;
    int iter, res;
    int counter = 0, cancelled = 0, time_steps = 0;

    std::ofstream f_out(out_csv_file_path);
    clock_t start_t_benchmark = clock();
    write_result(f_out, values, t);
    while (t < model_t) { // Time integrity
        iter = 0;
        time_info.t = t;
        time_info.dt = cur_dt;
        do { // Newton's method
            elements_loader.get_model_jacobian(jacobian, values, time_info);
            elements_loader.get_model_residual(residual, values, prev_values, time_info);

            #ifdef DEBUG
                std::cout << "Jacobian size: " << matrix_size << std::endl;
                std::cout << "Residual size: " << vector_size << std::endl;
                std::cout << std::endl << jacobian << std::endl << residual << std::endl;
            #endif

            // Операции с n-1 ными векторами и матрицами
            jacobian_cut = jacobian.block(1, 1, jacobian.rows() - 1, jacobian.cols() - 1);
            residual_cut = residual.tail(residual.size() - 1);

            #ifdef DEBUG
                std::cout << std::endl << jacobian_cut << std::endl << residual_cut << std::endl;
            #endif

            correction_cut = jacobian_cut.fullPivHouseholderQr().solve(residual_cut);

            correction.resize(correction_cut.size() + 1);
            correction.setZero(correction_cut.size() + 1);
            correction.tail(correction.size() - 1) = correction_cut;
            correction(0) = 0;
            // Конец операций с n-1 ными векторами и матрицами

            values = values + correction;
            iter++;
            counter++;
            res = check_error(correction, max_error, iter, max_iter);
        } while (res == 0);

        #ifndef FIXED_STEP
            if (res == -1) {
                cur_dt /= 2;
                values = prev_values;
                cancelled += iter;
                continue;
            }
            res = check_accuracy(values, prev_values, prev_prev_values, acr_min, acr_max, cur_dt);
            if (res == -1) {
                cur_dt /= 2;
                /*if (time_steps > 5) {
                    values = prev_values;
                    cancelled += iter;
                    continue;
                }*/
            }
            if (res == 1) {
                cur_dt *= 2;
                /*if (time_steps > 5) {
                    values = prev_values;
                    cancelled += iter;
                    continue;
                }*/
            }
        #endif // FIXED_STEP

        t += cur_dt;
        prev_prev_values = prev_values;
        prev_values = values;
        write_result(f_out, values, t);

        #ifndef WITHOUT_PREDICTION
            predict_initial(values, prev_values, prev_prev_values);
        #endif // WITHOUT_PREDICTION

        time_steps++;
    }
    clock_t end_t_benchmark = clock();
    f_out.close();

    std::cout << "Number of iterations: " << counter << std::endl;
    std::cout << "Cancelled iterations: " << cancelled << std::endl;
    std::cout << "Time steps: " << time_steps << std::endl;
    std::cout << "Calculation time (with writing to file): "
              << (double)(end_t_benchmark - start_t_benchmark) / CLOCKS_PER_SEC
              << " sec." << std::endl;

    return 0;
}


void predict_initial(Eigen::VectorXd &values, const Eigen::VectorXd &prev_values, const Eigen::VectorXd &prev_prev_values)
{
    values += (prev_values - prev_prev_values);
}

int check_error(const Eigen::VectorXd &correction, double max_error, int iter, int max_iter)
{
    if (iter > max_iter) return -1;
    if (correction.norm() < max_error) return 1;
    return 0;
}

int check_accuracy(const Eigen::VectorXd &values, const Eigen::VectorXd &prev_values, const Eigen::VectorXd &prev_prev_values, double acr_min, double acr_max, double cur_dt)
{
    double delta = ((values - prev_values)/cur_dt - (prev_values - prev_prev_values)/cur_dt).lpNorm<Eigen::Infinity>();
    delta = delta * cur_dt / 2;
    // std::cout << delta << std::endl;

    if (delta > acr_min) return -1;
    if (delta < acr_max) return 1;
    return 0;
}

void write_result(std::ofstream &f_out, Eigen::VectorXd &values, double t)
{
    f_out << t << ",";
    for (int i = 1; i < values.size(); i++)
    {
        f_out << values(i);
        if (i < values.size() - 1)
        {
            f_out << ",";
        }
        else
        {
            f_out << "\n";
        }
    }
}

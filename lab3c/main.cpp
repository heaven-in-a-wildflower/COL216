#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <thread>
#include <utility>
#include <vector>
using namespace std;
using namespace std::chrono;

int **allocateMatrix(int n)
{
    int **c = new int *[n];
    for (int i = 0; i < n; i++)
    {
        c[i] = new int[n];
    }
    return c;
}

void initialiseZeroMatrix(int **c, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            c[i][j] = 0;
        }
    }
}

void initialiseRandomMatrix(int **c, int n)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            c[i][j] = dis(gen);
        }
    }
}

void deallocateMatrix(int **c, int n)
{
    for (int i = 0; i < n; i++)
    {
        delete[] c[i];
    }
    delete[] c;
}

void printMatrix(int **c, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << c[i][j] << " ";
        }
        cout << endl;
    }
}

void mult_i_j_k(int **a, int **b, int **c, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void mult_i_k_j(int **a, int **b, int **c, int n)
{

    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k < n; k++)
        {
            for (int j = 0; j < n; j++)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void mult_j_i_k(int **a, int **b, int **c, int n)
{

    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int k = 0; k < n; k++)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void mult_j_k_i(int **a, int **b, int **c, int n)
{

    for (int j = 0; j < n; j++)
    {
        for (int k = 0; k < n; k++)
        {
            for (int i = 0; i < n; i++)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void mult_k_i_j(int **a, int **b, int **c, int n)
{

    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void mult_k_j_i(int **a, int **b, int **c, int n)
{

    for (int k = 0; k < n; k++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int i = 0; i < n; i++)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void transpose_i_j(int **a, int **b, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            a[i][j] = b[j][i];
        }
    }
}

void transpose_j_i(int **a, int **b, int n)
{
    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < n; i++)
        {
            a[i][j] = b[j][i];
        }
    }
}

int measureMultFunctionTime(void (*func)(int **, int **, int **, int), int **a,
                            int **b, int **c, int n)
{
    auto start = high_resolution_clock::now();
    func(a, b, c, n);
    auto stop = high_resolution_clock::now();
    return duration_cast<milliseconds>(stop - start).count();
}

int measureTransposeFunctionTime(void (*func)(int **, int **, int), int **a,
                                 int **b, int n)
{
    auto start = high_resolution_clock::now();
    func(a, b, n);
    auto stop = high_resolution_clock::now();
    return duration_cast<microseconds>(stop - start).count();
}

vector<double> measureTransposeTime(int **a, int **b, int n)
{
    vector<double> times(6, 0);

    vector<thread> threads;

    threads.push_back(thread(
        [&]()
        { times[0] = measureTransposeFunctionTime(transpose_i_j, a, b, n); }));
    threads.push_back(thread(
        [&]()
        { times[1] = measureTransposeFunctionTime(transpose_j_i, a, b, n); }));

    for (auto &t : threads)
    {
        if (t.joinable())
            t.join();
    }

    return times;
}

vector<double> measureMultTime(int **a, int **b, int **c, int n)
{
    vector<double> times(6, 0);

    vector<thread> threads;

    threads.push_back(thread(
        [&]() { times[0] = measureMultFunctionTime(mult_i_j_k, a, b, c, n); }));
    threads.push_back(thread(
        [&]() { times[1] = measureMultFunctionTime(mult_i_k_j, a, b, c, n); }));
    threads.push_back(thread(
        [&]() { times[2] = measureMultFunctionTime(mult_j_i_k, a, b, c, n); }));
    threads.push_back(thread(
        [&]() { times[3] = measureMultFunctionTime(mult_j_k_i, a, b, c, n); }));
    threads.push_back(thread(
        [&]() { times[4] = measureMultFunctionTime(mult_k_i_j, a, b, c, n); }));
    threads.push_back(thread(
        [&]() { times[5] = measureMultFunctionTime(mult_k_j_i, a, b, c, n); }));

    for (auto &t : threads)
    {
        if (t.joinable())
            t.join();
    }

    return times;
}

int main()
{
    vector<pair<int, vector<double>>> timings_mult;
    vector<pair<int, vector<double>>> timings_trans;

    for (int n = 1; n <= 500; n += 1)
    {
        // vector<double> sum_mult(6, 0);
        vector<double> sum_trans(2, 0);

        int **a = allocateMatrix(n);
        initialiseRandomMatrix(a, n);

        int **b = allocateMatrix(n);
        initialiseRandomMatrix(b, n);

        // int **c = allocateMatrix(n);
        // initialiseZeroMatrix(c, n);

        // for (int i = 1; i < 10; i++)
        // {
        //     vector<double> times = measureMultTime(a, b, c, n);
        //     for (int j = 0; j < 6; j++)
        //     {
        //         sum_mult[j] += times[j];
        //     }
        // }

        for (int i = 1; i < 10; i++)
        {
            vector<double> times = measureTransposeTime(a, b, n);
            for (int j = 0; j < 2; j++)
            {
                sum_trans[j] += times[j];
            }
        }

        // vector<double> avg_mult(6, 0);
        vector<double> avg_trans(2, 0);
        // for (int j = 0; j < 6; j++)
        // {
        //     avg_mult[j] = sum_mult[j] / 10.0;
        // }

        for (int j = 0; j < 2; j++)
        {
            avg_trans[j] = sum_trans[j] / 10.0;
        }

        deallocateMatrix(a, n);
        deallocateMatrix(b, n);
        // deallocateMatrix(c, n);
        // timings_mult.push_back(make_pair(n, avg_mult));
        timings_trans.push_back(make_pair(n, avg_trans));
        cout << n << " done" << endl;
    }

    // ofstream outfile("data1.txt");
    // if (!outfile)
    // {
    //     cerr << "Error opening file." << endl;
    //     return 1;
    // }

    // outfile
    //     << "mult_i_j_k mult_i_k_j mult_j_i_k mult_j_k_i mult_k_i_j mult_k_j_i"
    //     << endl;
    // for (auto &timing : timings_mult)
    // {
    //     outfile << timing.first << " ";
    //     for (auto &time : timing.second)
    //     {
    //         outfile << time << " ";
    //     }
    //     outfile << endl;
    // }
    //
    // outfile.close();

    ofstream outfile("data2.txt");
    if (!outfile)
    {
        cerr << "Error opening file." << endl;
        return 1;
    }

    outfile
        << "transpose_i_j transpose_j_i"
        << endl;
    for (auto &timing : timings_trans)
    {
        outfile << timing.first << " ";
        for (auto &time : timing.second)
        {
            outfile << time << " ";
        }
        outfile << endl;
    }

    return 0;
}

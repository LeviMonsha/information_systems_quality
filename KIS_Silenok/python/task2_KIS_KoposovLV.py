import numpy as np
import matplotlib.pyplot as plt
import math

def exs1():
    count_units = 1000
    ti1 = 3000
    count_rejected_units = 80

    p_uptime = (count_units - count_rejected_units) / count_units
    p_unit_failure = 1 - p_uptime

    print("Quest 1")
    print(f"P uptime: {p_uptime:.4f}")
    print(f"P unit failure: {p_unit_failure:.4f}")
    print()

def exs2():
    count_units = 1000
    ti1 = 3000
    count_rejected_units_ti1 = 80

    ti2 = 4000
    count_rejected_units_ti2 = 50

    failure_frequency_units_ti12 = count_rejected_units_ti2 / (count_units * (ti2 - ti1))
    failure_intensity_units_ti12 = count_rejected_units_ti2 / ((ti2 - ti1) * (count_units - count_rejected_units_ti1))

    print("Quest 2")
    print(f"Failure frequency time interval 3000-4000 h: {failure_frequency_units_ti12:.6f}")
    print(f"Failure intensity time interval 3000-4000 h: {failure_intensity_units_ti12:.6f}")
    print()

def exs3():
    print("Quest 3")
    N = 30
    count_units = 1000
    sep_t = 100

    tis = list(range(0, N*sep_t, sep_t))

    nds = [50, 40, 32, 25, 20, 17, 16, 16, 15, 14,
           15, 14, 14, 13, 14, 13, 13, 13, 14, 12,
           12, 13, 12, 13, 14, 16, 20, 25, 30, 40]

    ns = []
    Ps = []
    Qs = []
    as_ = []
    ns_mean = []
    lambdas = []

    cumulative_nds = 0

    for i in range(N):
        cumulative_nds += nds[i]

        ns_i = cumulative_nds + nds[i]
        ns.append(ns_i)
        Ps_i = (count_units - ns_i) / count_units
        Ps.append(Ps_i)
        Qs.append(1 - Ps_i)
        as_i = nds[i] / (count_units * sep_t)
        as_.append(as_i)
        ns_mean_i = ((count_units - ns_i) + (count_units - (ns_i - nds[i]))) / 2
        ns_mean.append(ns_mean_i)
        lambdas_i = nds[i] / (sep_t * (count_units - (ns_i - nds[i])))
        lambdas.append(lambdas_i)

    print(f"{'N':<3} {'time':<6} {'ns':<10} {'Ps':<10} {'Qs':<10} {'as':<12} {'ns_mean':<10} {'lambdas':<10}")
    for i in range(N):
        print(f"{i:<3} {tis[i]:<6} {ns[i]:<10} {Ps[i]:<10.3f} {Qs[i]:<10.3f} {as_[i]:<12.5f} {ns_mean[i]:<10.3f} {lambdas[i]:<10.5f}")

    plt.figure(figsize=(12, 10))

    plt.subplot(2, 2, 1)
    plt.plot(tis, Ps, color='green')
    plt.title("Probability of uptime")
    plt.xlabel("Time (h)")
    plt.ylabel("Ps")

    plt.subplot(2, 2, 2)
    plt.plot(tis, Qs, color='blue')
    plt.title("Probability of failure")
    plt.xlabel("Time (h)")
    plt.ylabel("Qs")

    plt.subplot(2, 2, 3)
    plt.plot(tis, as_, color='red')
    plt.title("Failure rate (as)")
    plt.xlabel("Time (h)")
    plt.ylabel("as")

    plt.subplot(2, 2, 4)
    plt.plot(tis, lambdas, color='orange')
    plt.title("Bounce rate (lambda)")
    plt.xlabel("Time (h)")
    plt.ylabel("lambda")

    plt.tight_layout()
    plt.show()

def main():
    exs1()
    exs2()
    exs3()

if __name__ == "__main__":
    main()

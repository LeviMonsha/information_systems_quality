import numpy as np
from scipy.stats import chi2

def mean(data):
    return np.mean(data) if len(data) > 0 else 0.0

def calculate_expected_frequencies(intervals, lambda_, N):
    expected_freq = []
    for left, right in intervals:
        if right == np.inf:
            prob = np.exp(-lambda_ * left)
        else:
            prob = np.exp(-lambda_ * left) - np.exp(-lambda_ * right)
        expected_freq.append(prob * N)
    return expected_freq

def calculate_chi_squared(observed, expected):
    chi_sq = 0.0
    for o, e in zip(observed, expected):
        if e > 0:
            chi_sq += (o - e)**2 / e
    return chi_sq

def main():
    N = 100
    K = 10
    ALPHA = 0.01

    np.random.seed()
    data = np.random.exponential(scale=1/ALPHA, size=N)
    print(data)

    max_value = np.max(data)
    interval_width = max_value / K

    intervals = [(i * interval_width, (i + 1) * interval_width) for i in range(K)]
    intervals[-1] = (intervals[-1][0], np.inf)

    observed = np.zeros(K, dtype=int)
    for num in data:
        for i, (left, right) in enumerate(intervals):
            if left <= num < right or (i == K - 1 and num >= left):
                observed[i] += 1
                break

    mean_value = mean(data)
    lambda_est = 1.0 / mean_value

    expected = calculate_expected_frequencies(intervals, lambda_est, N)

    chi_squared = calculate_chi_squared(observed, expected)
    degrees_of_freedom = K - 2

    p_value = chi2.sf(chi_squared, degrees_of_freedom)

    print(f"Chi-squared = {chi_squared:.4f}")
    print(f"Degrees of freedom = {degrees_of_freedom}")
    print(f"p-value = {p_value:.4e}")

    if p_value >= ALPHA:
        print("Гипотеза не может быть отклонена")
    else:
        print("Гипотеза отклонена")

if __name__ == "__main__":
    main()

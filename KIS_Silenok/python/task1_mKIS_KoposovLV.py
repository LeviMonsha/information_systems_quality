import math
import random
from scipy.stats import chi2

def main(
    N: int = 100,
    interval: tuple = (0, 100),
    K: int = 10,
    ALPHA: float = 0.01
) -> None:
    interval_width = (interval[1] - interval[0]) / K
    intervals = [
        (interval[0] + i * interval_width, 
         interval[0] + (i + 1) * interval_width)
        for i in range(K)
    ]
    
    random_nums = [random.uniform(*interval) for _ in range(N)]
    
    frequencies = [0] * K
    for num in random_nums:
        idx = min(int((num - interval[0]) // interval_width), K-1)
        frequencies[idx] += 1
    
    predicted_values = calculate_predicted(intervals, frequencies, N)
    
    observed, expected = merge_low_frequencies(frequencies, predicted_values)
    
    chi2_stat = calculate_chi2(observed, expected)
    df = degrees_of_freedom(len(observed), 1)
    
    critical_value = chi2.ppf(1 - ALPHA, df)
    p_value = 1 - chi2.cdf(chi2_stat, df)
    
    print_results(chi2_stat, critical_value, p_value, ALPHA, df)

def calculate_predicted(intervals, frequencies, N) -> list:
    mean_v = sum(
        (left + right)/2 * freq 
        for (left, right), freq in zip(intervals, frequencies)
    ) / N
    
    L = 1 / mean_v
    return [
        (math.exp(-L * left) - math.exp(-L * right)) * N
        for left, right in intervals
    ]

def merge_low_frequencies(observed, expected, min_freq: int = 5) -> tuple:
    merged_obs, merged_exp = [], []
    temp_obs, temp_exp = 0, 0
    
    for obs, exp in zip(observed, expected):
        if exp >= min_freq:
            if temp_exp > 0:
                merged_obs.append(temp_obs)
                merged_exp.append(temp_exp)
                temp_obs, temp_exp = 0, 0
            merged_obs.append(obs)
            merged_exp.append(exp)
        else:
            temp_obs += obs
            temp_exp += exp
    
    if temp_exp > 0:
        merged_obs.append(temp_obs)
        merged_exp.append(temp_exp)
    
    return merged_obs, merged_exp

def calculate_chi2(observed, expected) -> float:
    return sum(
        (obs - exp)**2 / exp 
        for obs, exp in zip(observed, expected) 
        if exp > 0
    )

def degrees_of_freedom(k: int, s: int) -> int:
    return k - s - 1

def print_results(chi2_stat, critical, p_val, alpha, df) -> None:
    print(f"Хи-квадрат: {chi2_stat:.3f}")
    print(f"Критическое значение ({alpha}): {critical:.3f}")
    print(f"Степени свободы: {df}")
    print(f"p-значение: {p_val:.5f}")
    
    if p_val < alpha:
        print("Вывод: Гипотеза отклоняется (распределение не соответствует)")
    else:
        print("Вывод: Гипотеза не может быть отклонена")

if __name__ == "__main__":
    main()

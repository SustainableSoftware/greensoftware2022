from distutils.log import warn
import scipy.stats as stat
import numpy as np
import pandas as pd
import math
import random

# Remove outliers from the initial data (per sample) 
# use quantile outliers when we do not have normal distributed data
def remove_outliers_quantile(data: pd.DataFrame):
    # data = data_series
    q75, q25 = data.quantile(q=0.75),data.quantile(q=0.25) # np.percentile(data.loc[:,data_column],[75,25])
    intr_qr = q75 - q25

    max = q75 + (1.5 * intr_qr)
    min = q25 - (1.5 * intr_qr)

    count_total = len(data)
    # data = data.dropna(axis=0)

    data = data[(data > min) & (data < max)]
    count_wo_outliers = len(data)

    outliers_count = count_total - count_wo_outliers
    print(f'number of outliers: {outliers_count} of {count_total} observations.')
    
    # remove outliers
    return data

# determines whether or not a sample follows a normal distribution
# https://stats.stackexchange.com/questions/350443/how-do-i-get-the-p-value-of-ad-test-using-the-results-of-scipy-stats-anderson
def anderson(data) -> float:
    ad, _, _ = stat.anderson(data)

    ad = ad * (1 + (.75/50) + 2.25/(50**2))

    if ad >= .6:
        p = math.exp(1.2937 - 5.709*ad - .0186*(ad**2))
    elif ad >= .34:
        p = math.exp(.9177 - 4.279*ad - 1.38*(ad**2))
    elif ad > .2:
        p = 1 - math.exp(-8.318 + 42.796*ad - 59.938*(ad**2))
    else:
        p = 1 - math.exp(-13.436 + 101.14*ad - 223.73*(ad**2))

    return p


# Cohen's d (https://machinelearningmastery.com/effect-size-measures-in-python/)
#   Measures the difference between the mean from two Gaussian-distributed variables. 
#   It is a standard score that summarizes the difference in terms of the number of standard deviations. 
#   Because the score is standardized, there is a table for the interpretation of the result, summarized as:
#     - Small Effect Size:  d=0.20
#     - Medium Effect Size: d=0.50
#     - Large Effect Size:  d=0.80
def cohend(d1, d2):
	# calculate the size of samples
	n1, n2 = len(d1), len(d2)
	# calculate the variance of the samples
	s1, s2 = np.var(d1, ddof=1), np.var(d2, ddof=1)
	# calculate the pooled standard deviation
	s = np.sqrt(((n1 - 1) * s1 + (n2 - 1) * s2) / (n1 + n2 - 2))
	# calculate the means of the samples
	u1, u2 = np.mean(d1), np.mean(d2)
	# calculate the effect size
	return (u1 - u2) / s

# Hedge's g (https://www.statology.org/hedges-g/) 
#   The only difference between Cohen’s d and Hedges’ g is that Hedges’ g takes each sample size into consideration when calculating the overall effect size.
#   Thus, it’s recommended to use Hedge’s g to calculate effect size when the two sample sizes are not equal.
#   If the two sample sizes are equal then Hedges’ g and Cohen’s d will be the exact same value.
#   Following is inspired by https://rowannicholls.github.io/python/statistics/effect_size.html#hedgess-g
def hedgesg(data_series1, data_series2):
    data1 = data_series1
    data2 = data_series2
    
    # degrees of freedom
    n1 = data1.count()
    n2 = data1.count()
    dof = n1+n2-2
    
    # Variances
    var1 = data1.var()
    var2 = data2.var()

    # Difference of the means
    mean1 = data1.mean()
    mean2 = data2.mean()    
    diff_mean = mean1-mean2

    # Pooled standard deviation
    s_pooled_star = np.sqrt((((n1 - 1) * var1) + ((n2 - 1) * var2)) / dof)

    # Hedges's g
    return diff_mean / s_pooled_star


# performs random sampling to compare two samples that are not normally distributed
#   H0: df1 and df2 have the same distribution, the difference in samples is due to chance
#   H1: df1's average is lower than df2's
def random_sampling(df1: pd.DataFrame, df2: pd.DataFrame, col: str, reps: int, log = True) -> tuple[float, list[float]]:
    
    df1_len, df2_len = len(df1), len(df2)

    if df1_len != df2_len and log:
        warn(f"The number of samples is not the same!\n\tdf1 : {df1_len}\n\tdf2 : {df2_len}")
    
    df = pd.concat([df1, df2])
    df.reset_index()
    df_len = len(df)

    max_combs = math.factorial(df_len) / (math.factorial(df1_len) * math.factorial(df_len - df1_len))
    if max_combs < reps and log:
        warn(f"The number of possible combinations is {max_combs}, and you are using {reps} repetitions!")

    list_idx = [*range(df_len)]
    
    mean_diffs = []
    for _ in range(reps):
        samples = random.sample(list_idx, df_len)
        sample1_idx = samples[:df1_len]
        sample2_idx = samples[df1_len:]

        sample1 = df.iloc[sample1_idx]
        sample2 = df.iloc[sample2_idx]

        mean_diff = sample1[col].mean() - sample2[col].mean()
        mean_diffs.append(mean_diff)

    org_mean_diff = df1[col].mean() - df2[col].mean()
    # pvalue = np.mean(abs(mean_diffs) >= abs(org_mean_diff))
    pvalue = np.mean([abs(x) >= abs(org_mean_diff) for x in mean_diffs])

    # pvalue = np.count_nonzero(pd.Series(mean_diffs) <= org_mean_diff) / reps

    return pvalue, mean_diffs, org_mean_diff
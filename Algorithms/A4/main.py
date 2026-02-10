import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
pip install scikit-learn
def main():
    file_path = r"C:\Users\sayak\OneDrive\Desktop\WorkSpace\College Assignments\Algo\A4\OnlineNewsPopularity.csv"
    df = pd.read_csv(file_path)
    
    # Basic info
    print(df.shape)
    print(df.head())
    
    # Simple histogram of shares
    sns.histplot(df['shares'], kde=True, bins=50)
    plt.show()


def naive_search(text: str, pattern: str) -> int:
    """
    Returns how many times 'pattern' occurs in 'text' using naive search.
    """
    count = 0
    for i in range(len(text) - len(pattern) + 1):
        match = True
        for j in range(len(pattern)):
            if text[i + j] != pattern[j]:
                match = False
                break
        if match:
            count += 1
    return count

# Example usage (uncomment to test):
# text_example = "ABABABA"
# pattern_example = "ABA"
# print(naive_search(text_example, pattern_example))



from sklearn.linear_model import LinearRegression
from sklearn.model_selection import cross_val_score

def stepwise_forward_selection(df, target_col, max_features=None):
    """
    Performs stepwise forward selection on dataframe 'df' to predict 'target_col'.
    Returns a list of selected features in the order they were added.
    """
    if max_features is None:
        max_features = len(df.columns) - 1

    # Prepare data (assumes all other columns are numeric features)
    features = list(df.select_dtypes(include=[float, int]).columns)
    if target_col in features:
        features.remove(target_col)
    selected_features = []
    best_features = []

    # Initialize model
    model = LinearRegression()

    while len(selected_features) < max_features:
        best_score = -1e9
        best_feature = None

        # Try adding one feature at a time to see which improves the score
        for f in features:
            if f not in selected_features:
                temp_list = selected_features + [f]
                X = df[temp_list]
                y = df[target_col]
                scores = cross_val_score(model, X, y, cv=5, scoring='r2')
                score_mean = scores.mean()

                if score_mean > best_score:
                    best_score = score_mean
                    best_feature = f

        if best_feature is None:
            break
        selected_features.append(best_feature)
        best_features.append((best_feature, best_score))

    return [f for (f, _) in best_features]


if __name__ == "__main__":
    main()
import pandas as pd

df = pd.read_csv("dat/fourierSeriesSolution.csv")

timesteps = []
for t_val in df.t.drop_duplicates():
    timesteps.append(
        df.loc[df.t == t_val].drop(columns=["t", "z"]).pivot("y", "x", "concentration")
    )


from matplotlib import pyplot as plt
import seaborn as sns

for timestep in range(len(timesteps)):
    fig, ax = plt.subplots()
    sns.heatmap(timesteps[timestep], vmin=0.0, vmax=1.0, ax=ax)
    fig.savefig(f"dat/timestep{timestep:03}.png")
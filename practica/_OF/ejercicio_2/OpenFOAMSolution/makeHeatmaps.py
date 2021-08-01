import pandas as pd

timesteps = []
for timestep in range(20):
    timesteps.append(
        pd.read_csv(
            f"dat/datafile_{timestep}.csv",
            names=["x", "y", "z", "concentration", "U0", "U1", "U2"],
            skiprows=1
        )
        .drop(columns=["z", "U0", "U1", "U2"])
        .drop_duplicates()
        .pivot("y", "x", "concentration")
    )


from matplotlib import pyplot as plt
import seaborn as sns

for timestep in range(len(timesteps)):
    fig, ax = plt.subplots()
    sns.heatmap(timesteps[timestep], vmin=0.0, vmax=1.0, ax=ax)
    fig.savefig(f"dat/timestep_{timestep:03}.png")

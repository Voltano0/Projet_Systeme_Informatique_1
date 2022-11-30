import pandas as pd
import matplotlib.pyplot as plt

# Read the data
df = pd.read_csv('temp/output.csv',sep=";")
#plot the data for Producer_Consumer
for prog in df['Program'].unique():
    newdf = df[df['Program'] == prog]
    MeanTimes = []
    StdTimes = []
    RawTimes = []
    Nthreads = [1, 2, 4, 8, 16, 32, 64]
    for i in Nthreads:
        RawTimes.append(list(newdf[newdf['Threads'] == i]['Temps']))
        MeanTimes.append(newdf[newdf['Threads'] == i]['Temps'].mean())
        StdTimes.append(newdf[newdf['Threads'] == i]['Temps'].std())
    plt.clf()
    plt.boxplot(RawTimes, labels=Nthreads,showmeans=True)
    #plt.errorbar(Nthreads, MeanTimes, yerr=StdTimes, fmt='o')
    plt.ylim(ymin=0)
    plt.xlabel('Number of threads')
    plt.ylabel('Time (ms)')
    plt.title(prog)
    plt.savefig(f'temp/{prog}.png')
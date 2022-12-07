import pandas as pd
import matplotlib.pyplot as plt

# Read the data
df = pd.read_csv('temp/output.csv',sep=";")
tottime = df['Temps'].sum()
print(f"Temps Total = {tottime} s")
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
    if(list[i] == "Producer_Consumer" or list[i] == "Writer_Reader"):
        MeanTimes = MeanTimes[:len(MeanTimes)-1]
        StdTimes = StdTimes[:len(StdTimes)-1]
        RawTimes = RawTimes[:len(RawTimes)-1]
        MeanTimes.insert(1,MeanTimes[0])
        StdTimes.insert(1,StdTimes[0])
        RawTimes.insert(1,RawTimes[0])

    plt.boxplot(RawTimes, labels=Nthreads,showmeans=True)
    #plt.errorbar(Nthreads, MeanTimes, yerr=StdTimes, fmt='o')
    plt.ylim(ymin=0)
    plt.xlabel('Number of threads')
    plt.ylabel('Time (s)')
    plt.title(prog)
    plt.savefig(f'temp/{prog}.png')
plt.clf()
for i in range(0,df['Program'].unique().size,2):
    list = df['Program'].unique()
    newdf1 = df[df['Program'] == list[i]]
    newdf2 = df[df['Program'] == list[i+1]]
    MeanTimes1 = []
    MeanTimes2 = []
    StdTimes1 = []
    StdTimes2 = []
    RawTimes1 = []
    RawTimes2 = []
    Nthreads = [1, 2, 4, 8, 16, 32, 64]
    for j in Nthreads:
        MeanTimes1.append(newdf1[newdf1['Threads'] == j]['Temps'].mean())
        MeanTimes2.append(newdf2[newdf2['Threads'] == j]['Temps'].mean())
        StdTimes1.append(newdf1[newdf1['Threads'] == j]['Temps'].std())
        StdTimes2.append(newdf2[newdf2['Threads'] == j]['Temps'].std())
    plt.clf()
    #plt.boxplot(RawTimes, labels=Nthreads,showmeans=True)
    if(list[i] == "Producer_Consumer" or list[i] == "WriterReader"):
        MeanTimes1 = MeanTimes1[:len(MeanTimes1)-1]
        MeanTimes2 = MeanTimes2[:len(MeanTimes2)-1]
        StdTimes1 = StdTimes1[:len(StdTimes1)-1]
        StdTimes2 = StdTimes2[:len(StdTimes2)-1]
        MeanTimes1.insert(1,MeanTimes1[0])
        MeanTimes2.insert(1,MeanTimes2[0])
        StdTimes1.insert(1,StdTimes1[0])
        StdTimes2.insert(1,StdTimes2[0])
    plt.errorbar(Nthreads, MeanTimes1, yerr=StdTimes1, label=list[i])
    plt.errorbar(Nthreads, MeanTimes2, yerr=StdTimes2, label=list[i+1])
    plt.ylim(ymin=0)
    plt.xlabel('Number of threads')
    plt.xticks(Nthreads)
    plt.ylabel('Time (s)')
    plt.title(f"{list[i]} and {list[i+1]}")
    plt.legend()
    plt.savefig(f'temp/{list[i]}-{list[i+1]}.png')
plt.clf()
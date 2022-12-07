import pandas as pd
import matplotlib.pyplot as plt

# Read the data
df = pd.read_csv('temp/output.csv',sep=";")
totTime = df['Temps'].sum()
print(f"Temps Total = {totTime} s")
#plot the data for Producer_Consumer
for prog in df['Program'].unique():
    newDF = df[df['Program'] == prog]
    meanTimes = []
    stdTimes = []
    rawTimes = []
    nThreads = [1, 2, 4, 8, 16, 32, 64]
    for i in nThreads:
        rawTimes.append(list(newDF[newDF['Threads'] == i]['Temps']))
        meanTimes.append(newDF[newDF['Threads'] == i]['Temps'].mean())
        stdTimes.append(newDF[newDF['Threads'] == i]['Temps'].std())
    plt.clf()
    if(prog == "Producer_Consumer" or prog == "WriterReader" or prog == "Producer_Consumer_AC" or prog == "WriterReader_AC"):
        nThreads = nThreads[1:len(nThreads)]
        meanTimes = meanTimes[:len(meanTimes)-1]
        stdTimes = stdTimes[:len(stdTimes)-1]
        rawTimes = rawTimes[:len(rawTimes)-1]
    if(prog=="Philosof"):
        prog = "Philosophe"
    if(prog=="Philosof_AC"):
        prog = "Philosophe_AC"
    plt.boxplot(rawTimes, labels=nThreads,showmeans=True)
    #plt.errorbar(nThreads, meanTimes, yerr=stdTimes, fmt='o')
    plt.ylim(ymin=0)
    plt.xlabel('Number of threads')
    plt.ylabel('Time (s)')
    plt.title(prog)
    plt.savefig(f'temp/{prog}.pdf')
    
plt.clf()
for i in range(0,df['Program'].unique().size,2):
    list = df['Program'].unique()
    newDF1 = df[df['Program'] == list[i]]
    newDF2 = df[df['Program'] == list[i+1]]
    meanTimes1 = []
    meanTimes2 = []
    stdTimes1 = []
    stdTimes2 = []
    rawTimes1 = []
    rawTimes2 = []
    nThreads = [1, 2, 4, 8, 16, 32, 64]
    for j in nThreads:
        meanTimes1.append(newDF1[newDF1['Threads'] == j]['Temps'].mean())
        meanTimes2.append(newDF2[newDF2['Threads'] == j]['Temps'].mean())
        stdTimes1.append(newDF1[newDF1['Threads'] == j]['Temps'].std())
        stdTimes2.append(newDF2[newDF2['Threads'] == j]['Temps'].std())
    plt.clf()
    #plt.boxplot(rawTimes, labels=nThreads,showmeans=True)
    if(list[i] == "Producer_Consumer" or list[i] == "WriterReader"):
        meanTimes1 = meanTimes1[:len(meanTimes1)-1]
        meanTimes2 = meanTimes2[:len(meanTimes2)-1]
        stdTimes1 = stdTimes1[:len(stdTimes1)-1]
        stdTimes2 = stdTimes2[:len(stdTimes2)-1]
        nThreads = nThreads[1:len(nThreads)]
    if(list[i]=="Philosof"):
        list[i] = "Philosophe"
        list[i+1] = "Philosophe_AC"
    plt.errorbar(nThreads, meanTimes1, yerr=stdTimes1, label=list[i])
    plt.errorbar(nThreads, meanTimes2, yerr=stdTimes2, label=list[i+1])
    plt.ylim(ymin=0)
    plt.xlabel('Number of threads')
    plt.xticks(nThreads)
    plt.ylabel('Time (s)')
    plt.title(f"{list[i]} and {list[i+1]}")
    plt.legend()
    plt.savefig(f'temp/{list[i]}-{list[i+1]}.pdf')
plt.clf()
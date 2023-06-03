import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt



df = pd.read_csv("runtimeoptimizado.csv")
df2 = pd.read_csv("runtimenooptimizado.csv")
df3 = pd.read_csv("runtimedenso.csv")





df3['time'] = (df3['time'])
df3['cota'] = (df3['n'])

df['time'] = df['time']
df['cota'] = (df['n'])




df2['time'] = (df2['time'])
df2['cota'] = (df2['n'])


fig, ax = plt.subplots()

r = np.corrcoef(df['time'], df['cota'])[0, 1];
r2 = np.corrcoef(df2['time'], df2['cota'])[0, 1];
r3 = np.corrcoef(df3['time'], df3['cota'])[0, 1];
print("El coeficiente de correlación de Pearson es: r="+str(r))

print("El coeficiente de correlación de Pearson es: r2="+str(r2))
print("El coeficiente de correlación de Pearson es: r3="+str(r3))

df3['log_time'] = (df3['time'])
df3['log_cota'] = np.log(df3['n'])

df['log_time'] = (df['time'])
df['log_cota'] = (df['n'])




df2['log_time'] = (df2['time'])
df2['log_cota'] = (df2['n'])


ax.scatter(df2['log_cota'],df2['log_time'],color='blue')
ax.scatter(df['log_cota'], df['log_time'],color='red')
ax.plot(df['log_cota'],df['log_time'],color='red', label='optimizado')
ax.plot(df2['log_cota'],df2['log_time'],color='blue', label='no optimizado')
ax.scatter(df3['log_cota'],df3['log_time'],color='green')
ax.plot(df3['log_cota'],df3['log_time'],color='green', label='denso')
plt.xlabel("log_tiempo (s)")
plt.ylabel("log_cota")

#rojo ordenado df

ax1 = sns.lmplot(x='log_time', y='log_cota', data=df, line_kws={'color': 'red'} , scatter_kws={"color": "red"} ) #verrrrrrrrrrrrrrrrr
ax2 = sns.lmplot(x='log_time', y='log_cota', data=df2, line_kws={'color': 'blue'})
ax3 = sns.lmplot(x='log_time', y='log_cota', data=df3, line_kws={'color': 'green'})

ax.legend()
ax.grid(True)

plt.show()


# fig = plt.figure()


# df['cota'] = df['n']
# dfOrd['cota'] = dfOrd['n']



# ax1 = sns.lmplot(x='time', y='cota', data=df)
# plt.xlabel("tiempo (s)")
# plt.ylabel("cota teorica")



# df['log_time'] = np.log(df['time'])
# df['log_cota'] = np.log(df['cota'])
# ax1 = sns.lmplot(x='log_time', y='log_cota', data=df)
# plt.xlabel("log_tiempo (s)")
# plt.ylabel("log_cota")



# plt.show()
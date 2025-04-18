import pandas as pd
import matplotlib.pyplot as plt


res_filepath = "./results.csv"
res_picpath  = "./graphics.png"

col_filepath = "./collisions.csv"
col_picpath  = "./collisions.png"

results = pd.read_csv(res_filepath)

names = results.columns[1:]


plt.figure(figsize=(10,10),layout="tight")



plt.subplot(211)

plt.title("Зависимость времени поиска от количества элементов для различных методов")

for name in names:
  plt.plot(results["Size"], results[name], "--o")
  
plt.grid(linestyle=":")
plt.legend(results.columns[1:])

plt.xlabel("Количесто элементов")
plt.ylabel("Время поиска, µs")


plt.subplot(212)

for name in names:
  plt.plot(results["Size"], results[name], "--o")
  
plt.grid(linestyle=":")
plt.legend(results.columns[1:])

plt.xlabel("Количесто элементов")
plt.ylabel("Время поиска, µs")

plt.yscale("log")


plt.savefig(res_picpath)


collisions = pd.read_csv(col_filepath)

plt.figure(figsize=(10,5),layout="tight")



plt.title("Зависимость коллизий в хеш-таблице от количества элементов в наборе данных")

plt.plot(collisions["Size"], collisions["Collisions"], "--ob")
  
plt.grid(linestyle=":")

plt.xlabel("Количесто элементов")
plt.ylabel("Количество коллизий")

plt.xscale("log")

plt.savefig(col_picpath)

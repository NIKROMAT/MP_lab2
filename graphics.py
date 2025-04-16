import pandas as pd
import matplotlib.pyplot as plt


filepath = "./results.csv"
picpath  = "./graphics.png"

results = pd.read_csv(filepath)

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


plt.savefig(picpath)


import pandas as pd
import numpy as np
import random as rand
import os


date_lims = ("2000-01-01","2024-12-31")

def generate_dataset(size: int, target: str = None) -> pd.DataFrame:

  target_rate = 0.001
  train_types = "скорый пассажирский товарный".split(' ')
  date_range = pd.date_range(start=date_lims[0],end=date_lims[1],freq="D").astype(str)


  df = pd.DataFrame(columns=["No","Date","Type","Departure time","Travel time"])

  df["No"] = np.random.randint(1000000, size=size).astype(str)
  df["No"] = df["No"].str.rjust(6,'0')

  df["Date"] = rand.choices(date_range, k=size)

  df["Type"] = rand.choices(train_types, k=size)

  df["Departure time"] = [str(pd.to_datetime(offset, unit='m', origin=pd.Timestamp("00:00:00")).time()) for offset in np.random.randint(24*60, size=size)]
  df["Travel time"]    = [str(pd.to_datetime(offset, unit='m', origin=pd.Timestamp("00:00:00")).time()) for offset in np.random.randint(24*60, size=size)]


  target_num = max(3, int(size*target_rate))
  lst = rand.sample(range(size), target_num)
  print( lst)

  df.loc[lst, "Date"] = target


  return df


SIZE = [100,200,300,500,1000,10000,20000,30000,40000,50000,60000,70000,80000,90000,100000]
datasets_folder = "./datasets/"

target_key = rand.choice(pd.date_range(start=date_lims[0],end=date_lims[1],freq="D").astype(str))


with open("target_key.txt", "w") as file:
  file.write(target_key)

print(f"Target: {target_key}\n")


os.makedirs(datasets_folder, exist_ok=True)

for i, size in enumerate(SIZE):
  dataset_path = datasets_folder + f"dataset_{i+1}.csv"
  generate_dataset(size, target=target_key).to_csv(dataset_path, index=False)
  print(f"Size {size} done\n")


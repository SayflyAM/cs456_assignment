import matplotlib.pyplot as plt

genrations = []
fitness_values = []


with open("results.txt", "r") as file:

    for line in file:
        if "Run 4" in line :
            break
        if "Best Fitness" in line:
            data =line.split()
            print(data)
            genrations.append(int(data[1]))
            fitness_values.append(int(data[5]))


            

plt.plot(genrations, fitness_values)
plt.xlabel("Genration")
plt.ylabel("Best Fitness")

plt.title("we use tournamentSelection Run 4")
#plt.title("Roulette Wheel Run 4 ")
plt.show()
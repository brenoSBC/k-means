import matplotlib.pyplot as plt

fig = plt.figure()
ax = fig.add_subplot(projection="3d")

x = []
y = []
z = []
clusters = []

with open("points.txt", "r") as dataset:

    for line in dataset:
        values = line.split()

        x.append(float(values[0]))
        y.append(float(values[1]))
        z.append(float(values[2]))
        clusters.append(int(values[3]))

cx = []
cy = []
cz = []

with open("centroids.txt", "r") as centroids:

    for line in centroids:
        values = line.split()

        cx.append(float(values[0]))
        cy.append(float(values[1]))
        cz.append(float(values[2]))

ax.scatter(x, y, z, c=clusters)
ax.scatter(cx, cy, cz, marker="X", s=300)

ax.set_xlabel("X")
ax.set_ylabel("Y")
ax.set_zlabel("Z")

plt.show()
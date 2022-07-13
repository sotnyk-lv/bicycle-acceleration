from matplotlib import projections
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.animation as animation

# This function is called periodically from FuncAnimation
def animate(i):
    global vectors

    line = file.readline()
    if line == '':
        file.close()
        exit()
    acc = [.0,.0,.0] + list(map(float, line.split('\t')[1:4]))
    vectors = np.delete(vectors, 0, axis=0)
    vectors = np.append(vectors, [np.array(acc)], axis=0)

    X, Y, Z, U, V, W = zip(*vectors)
    # print(vectors, np.array(acc))

    # Draw x and y lists
    ax.clear()
    ax.set_xlim(-2, 2)
    ax.set_ylim(-2, 2)
    ax.set_zlim(-2, 2)

    # alpha_chan = np.linspace(0.1,1,10)
    color = ('red','blue','white','black','red','blue','white','black','red','blue')
    alpha_chan = np.append(np.zeros(8), (1,1))

    ax.quiver(X, Y, Z, U, V, W, alpha=alpha_chan, color = color)

file = open('../resources/acc_mag_res.list', 'r')

global vectors


try:

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    ax.set_xlim(-2, 2)
    ax.set_ylim(-2, 2)
    ax.set_zlim(-2, 2)

    vectors = np.zeros((10,6))



    # Set up plot to call animate() function periodically
    ani = animation.FuncAnimation(fig, animate, interval=1)
    ani.save('../resources/acc_vec.mp4', writer = 'ffmpeg', fps = 10)

    plt.show()

except Exception as exc:
    print(exc)
finally:
    file.close()


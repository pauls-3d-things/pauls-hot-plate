import matplotlib.pyplot as plt
import matplotlib.animation as animation
import serial
import time
import sys

# The following blog post helped me write this:
# http://www.mikeburdis.com/wp/notes/plotting-serial-port-data-using-python-and-matplotlib/

if len(sys.argv) < 3:
    print("Usage: python main.py <path-to-serial> <baud-rate>")
    exit(1)

# open serial interface
ser = serial.Serial()
ser.port = sys.argv[1]
ser.baudrate = int(sys.argv[2])
ser.timeout = 10
ser.open()
if ser.is_open == True:
    print("\nAll right, serial port now open. Configuration:\n")
    print(ser, "\n")
else:
    exit(2)

# create figure
fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)
xs = []
ys = []
startTime = time.time()


def update(frame, xs, ys):

    line = ser.readline()
    line_as_list = line.split(b',')
    i = float(line_as_list[0])
    t = time.time() - startTime
    print(t, i)
    xs.append(t)
    ys.append(i)

    # Limit x and y lists to 20 items
    #xs = xs[-20:]
    #ys = ys[-20:]

    ax.clear()

    # Add horizontal
    for yc in range(0, 300, 10):
        plt.axhline(y=yc, color='whitesmoke', linestyle='--')
    for xc in range(0, 440, 10):
        plt.axvline(x=xc, color='whitesmoke', linestyle='--')
    ax.plot(xs, ys, label="Channel 0")

    # Format plot
    plt.xticks(rotation=45, ha='right')
    plt.subplots_adjust(bottom=0.30)
    plt.title(ser.port)
    plt.ylabel('Temperature (C)')
    plt.xlabel('Time (Seconds)')
    plt.legend()
    plt.axis([0, 420, 0, 260])


ani = animation.FuncAnimation(fig, update, fargs=(xs, ys), interval=500)

plt.show()

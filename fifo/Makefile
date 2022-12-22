TARGET1=P1
TARGET2=P2
TARGET3=fifoCreator
SOURCE1=P1.c
SOURCE2=P2.c
SOURCE3=main.c

all: $(TARGET1) $(TARGET2) $(TARGET3)

$(TARGET1):
		gcc $(SOURCE1) -o P1
$(TARGET2):
		gcc $(SOURCE2) -o P2
$(TARGET3):
		gcc $(SOURCE3) -o fifoCreator

runP1:
		./$(TARGET1)
runP2:
		./$(TARGET2)
runF:
		./$(TARGET3)

clean:
		rm -f $(TARGET1) $(TARGET2) $(TARGET3)
		rm -f /tmp/intFifo 
		rm -f /tmp/stringFifo
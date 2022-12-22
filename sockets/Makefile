TARGET1=P1
TARGET2=P2
SOURCE1=P1.c
SOURCE2=P2.c

all: $(TARGET1) $(TARGET2)

$(TARGET1):
		gcc $(SOURCE1) -o P1
$(TARGET2):
		gcc $(SOURCE2) -o P2

runP1:
		./$(TARGET1)
runP2:
		./$(TARGET2)

clean:
		rm -rf $(TARGET1) $(TARGET2)
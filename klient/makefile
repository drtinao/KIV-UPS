JFLAGS = -g
JVM= java
JC = javac

.SUFFIXES: .java .class

.java.class:
	$(JC) $(JFLAGS) $*.java

CLASSES = \
		  ClientConnection.java \
		  Connect.java \
		  Game.java \
		  Lobby.java \
		  Starter.java

default: classes

classes: $(CLASSES:.java=.class)

clean:
	$(RM) *.class

run:
	java Starter

COMP = g++
OBJS = Auxiliary.o BoardIO.o FilePlayerAlgorithm.o Game.o GameLogic.o GameManager.o GamePiece.o main_TournamentManager.o \
	MyBoard.o MyFightInfo.o MyJokerChange.o MyMove.o MyPiecePosition.o MyPoint.o PlannedMove.o TournamentManager.o \
	AlgorithmRegistration.o
PLAYER_OBJS = RSPPlayer_208940601.o PlannedMove.o GamePiece.o MyPoint.o MyBoard.o Auxiliary.o MyPiecePosition.o MyJokerChange.o MyMove.o

EXEC = ex3
CPP_COMP_FLAG =  -std=c++14 -Wall -Wextra \
-Werror -pedantic-errors -DNDEBUG

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) -rdynamic -ldl -pthread -o $@
RSPPlayer_208940601.so: $(PLAYER_OBJS)
	$(COMP) $(PLAYER_OBJS) -shared -o $@
Auxiliary.o: Auxiliary.cpp Auxiliary.h
	$(COMP) -fPIC $(CPP_COMP_FLAG) -c $*.cpp
BoardIO.o: BoardIO.cpp BoardIO.h Auxiliary.h GameLogic.h Game.h MyBoard.h Board.h GamePiece.h \
	FightInfo.h PlannedMove.h Point.h MyPoint.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
FilePlayerAlgorithm.o: FilePlayerAlgorithm.cpp FilePlayerAlgorithm.h PlayerAlgorithm.h Point.h \
	PiecePosition.h Board.h FightInfo.h Move.h JokerChange.h PlannedMove.h GamePiece.h MyPoint.h \
	MyBoard.h Auxiliary.h MyMove.h MyJokerChange.h MyPiecePosition.h BoardIO.h GameLogic.h Game.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Game.o: Game.cpp Game.h MyBoard.h Board.h GamePiece.h Auxiliary.h FightInfo.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
GameLogic.o: GameLogic.cpp GameLogic.h Game.h MyBoard.h Board.h GamePiece.h Auxiliary.h FightInfo.h \
	PlannedMove.h Point.h MyPoint.h MyFightInfo.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
GameManager.o: GameManager.cpp GameManager.h Game.h MyBoard.h Board.h GamePiece.h Auxiliary.h \
	FightInfo.h BoardIO.h GameLogic.h PlannedMove.h Point.h MyPoint.h PlayerAlgorithm.h \
	PiecePosition.h Move.h JokerChange.h MyFightInfo.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
GamePiece.o: GamePiece.cpp GamePiece.h Auxiliary.h
	$(COMP) -fPIC $(CPP_COMP_FLAG) -c $*.cpp
main_TournamentManager.o: main_TournamentManager.cpp Auxiliary.h BoardIO.h GameLogic.h Game.h MyBoard.h Board.h GamePiece.h FightInfo.h \
	PlannedMove.h Point.h MyPoint.h GameManager.h PlayerAlgorithm.h PiecePosition.h Move.h \
	JokerChange.h FilePlayerAlgorithm.h RSPPlayer_208940601.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
MyBoard.o: MyBoard.cpp MyBoard.h Board.h GamePiece.h Auxiliary.h Point.h
	$(COMP) -fPIC $(CPP_COMP_FLAG) -c $*.cpp
MyFightInfo.o: MyFightInfo.cpp MyFightInfo.h FightInfo.h MyPoint.h Point.h Auxiliary.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
MyJokerChange.o: MyJokerChange.cpp MyJokerChange.h JokerChange.h MyPoint.h Point.h GamePiece.h
	$(COMP) -fPIC $(CPP_COMP_FLAG) -c $*.cpp
MyMove.o: MyMove.cpp MyMove.h Move.h MyPoint.h Point.h
	$(COMP) -fPIC $(CPP_COMP_FLAG) -c $*.cpp
MyPiecePosition.o: MyPiecePosition.cpp MyPiecePosition.h PiecePosition.h MyPoint.h Point.h
	$(COMP) -fPIC $(CPP_COMP_FLAG) -c $*.cpp
MyPoint.o: MyPoint.cpp MyPoint.h Point.h
	$(COMP) -fPIC $(CPP_COMP_FLAG) -c $*.cpp
PlannedMove.o: PlannedMove.cpp PlannedMove.h GamePiece.h Point.h MyPoint.h
	$(COMP) -fPIC $(CPP_COMP_FLAG) -c $*.cpp
TournamentManager.o: TournamentManager.cpp TournamentManager.h PlayerAlgorithm.h AlgorithmRegistration.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
AlgorithmRegistration.o: AlgorithmRegistration.cpp \
  AlgorithmRegistration.h PlayerAlgorithm.h Point.h PiecePosition.h \
  Board.h FightInfo.h Move.h JokerChange.h TournamentManager.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

RSPPlayer_208940601.o: RSPPlayer_208940601.cpp RSPPlayer_208940601.h PlayerAlgorithm.h Point.h PiecePosition.h Board.h \
	FightInfo.h Move.h JokerChange.h PlannedMove.h GamePiece.h MyPoint.h MyBoard.h Auxiliary.h AlgorithmRegistration.h \
	MyPiecePosition.h MyJokerChange.h MyMove.h
	$(COMP) -fPIC $(CPP_COMP_FLAG) -c $*.cpp

.PHONY: all
all: $(EXEC) RSPPlayer_208940601.so
.PHONY: rps_tournament
rps_tournament: $(EXEC)
.PHONY: rps_lib
rps_lib: RSPPlayer_208940601.so
clean:
	rm -f $(OBJS) RSPPlayer_208940601.o RSPPlayer_208940601.so $(EXEC)


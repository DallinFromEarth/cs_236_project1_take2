cmake_minimum_required(VERSION 3.16.3)
project(project_1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(project_1
        Automaton.h
        ColonAutomaton.cpp
        ColonAutomaton.h
        ColonDashAutomaton.cpp
        ColonDashAutomaton.h
        Lexer.cpp
        Lexer.h
        main.cpp
        Token.cpp
        Token.h MatcherAutomaton.cpp MatcherAutomaton.h KeywordAutomaton.cpp KeywordAutomaton.h IDAutomaton.cpp IDAutomaton.h StringAutomaton.cpp StringAutomaton.h CommentAutomaton.cpp CommentAutomaton.h Parser.cpp Parser.h Parameter.h Predicate.cpp Predicate.h Rule.h DatalogProgram.cpp DatalogProgram.h Rule.cpp Tuple.cpp Tuple.h RelationHeader.h Relation.cpp Relation.h Database.cpp Database.h Interpreter.cpp Interpreter.h Graph.cpp Graph.h)

# Copyright (c) 2013 Flowgrammable, LLC.
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at:
# 
# http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an "AS IS"
# BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
# or implied. See the License for the specific language governing
# permissions and limitations under the License.

CXX=g++
CXX_FLAGS=-Wall -g -std=c++11 -I..

TARGET=cfg
OBJS= config.o token.o parser.o tcheck.o environment.o eval.o main.o 

$(TARGET): $(OBJS)
	$(CXX) $(CXX_FLAGS) -o $@ $^

%.o:%.cpp
	$(CXX) $(CXX_FLAGS) -c $^

clean:
	rm -f $(TARGET)
	rm -f *.o

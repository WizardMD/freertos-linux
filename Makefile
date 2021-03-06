#   Copyright 2016 sean93.park@gmail.com
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.

OUTPUT_ROOT     := "build"

.phony: all clean arm

all:
	make -f Makefile.x86

arm:
	make -f Makefile.arm

osx:
	make -f Makefile_osx.x86

clean:
	rm -rf $(OUTPUT_ROOT)

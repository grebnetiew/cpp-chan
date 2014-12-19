require 'rake/clean'
CLEAN.include("**/*.o")
CLOBBER.include("main")
SRC = FileList["**/*.cc"]
OBJ = SRC.ext("o")

rule '.o' => '.cc' do |t|
  sh "g++ --std=c++11 -Wall -pthread -c -g -o \"#{t.name}\" \"#{t.source}\""
end

file 'main' => OBJ do
  sh "g++ --std=c++11 -Wall -lpthread -lstdc++ -o main #{OBJ.map{|f| "\"#{f}\"" }}"
end

task :default => 'main'

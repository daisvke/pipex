# pipex
This program mimics pipes and redirections of the Unix system

## Installation
```
git clone git@github.com:daisvke/pipex.git
make
```

## Description
* pipex should be executed in this way:
```
./pipex file1 cmd1 cmd2 file2
```
Where file1 is the file from which we read, cmd1 and cmd2 are shell commands with their parameters,
and finally file2 is the file in which we write the output from the last command.
* The execution of the pipex program should do the same as the next shell command:
```
< file1 cmd1 | cmd2 > file2
```
* It handles multiple pipes:
```
./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2

Ex.:
./pipex test/text cat "sed s/this/THIS/" "sed s/THAT/that/" "sed s/THIS_one/ThIs_OnE/" output
```
<p align=center>
   <img src="/screenshots/multiple_pipes.png" width="80%" />
</p>

* It supports '<<' and '>>' when the first parameter is "here_doc":
```
./pipex here_doc LIMITER cmd cmd1 cmd2 cmd3 ... file

Ex.:
./pipex here_doc LIMITER cat "cat -e" "sed 's/e/E/g' 's/i/I/g'" "awk NR==1" output 
```

<p align=center>
  <img src="/screenshots/multiple_pipes_and_heredoc.png" width="80%" />
</p>

Which is equivalent to:
```
cmd << LIMITER | cmd1 >> file
```

* It can run commands given by an absolute path, such as:
```
./pipex test/text "/bin/ls" "cat -e" output
```

* Or by a relative path, such as:
```
./pipex test/text "./test/cmd.sh" "cat -e" output
```


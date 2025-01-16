# **pipex**

This program mimics pipes and redirections in a Unix-like system.

---

## **Description**

### **Usage**  
The **pipex** program should be executed with the following syntax:

```bash
make
./pipex file1 cmd1 cmd2 file2
```

Where:
- **file1** is the file from which we read input.
- **cmd1** and **cmd2** are the shell commands with their respective parameters.
- **file2** is the file where the output of the last command will be written.

### **Shell Command Equivalent**
The execution of the **pipex** program should behave the same as the following shell command:

```bash
< file1 cmd1 | cmd2 > file2
```

---

### **Multiple Pipes Support**
**pipex** handles multiple pipes. For example:

```bash
./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
```

#### **Example:**

```bash
./pipex test/text cat "sed s/this/THIS/" "sed s/THAT/that/" "sed s/THIS_one/ThIs_OnE/" output
```

<p align="center">
   <img src="/screenshots/multiple_pipes.png" width="80%" />
</p>

---

### **Here Document Support (<< and >>)**  
**pipex** also supports **'<<'** and **'>>'** when the first parameter is `here_doc`. This allows for input redirection from a string (the **LIMITER**).

```bash
./pipex here_doc LIMITER cmd cmd1 cmd2 cmd3 ... file
```

#### **Example:**

```bash
./pipex here_doc LIMITER cat "cat -e" "sed s/e/E/g" "sed s/i/I/g" "awk NR==1" output 
```

<p align="center">
  <img src="/screenshots/multiple_pipes_and_heredoc.png" width="80%" />
</p>

Which is equivalent to:

```bash
cmd << LIMITER | cmd1 >> file
```

---

### **Absolute and Relative Path Support**
**pipex** can run commands specified by either an **absolute path** or a **relative path**.

#### **Example with Absolute Path:**

```bash
./pipex test/text "/bin/ls" "cat -e" output
```

#### **Example with Relative Path:**

```bash
./pipex test/text "./test/cmd.sh" "cat -e" output
```

View in a different language: [toki pona](nasin_kepeken-tok.md "lukin kepeken toki pona")

# **Documentation for ilo li sina**

ilo li sina is a small, string-only esoteric programming language. But you can still build interesting and useful things with it.

Everything in this language consists of or works with strings. You can create a string literal by encasing some text within quotes (i.e. "test" "this is a string literal".)

## **Language features**

---------------

### ***Functions***

ilo li sina has a couple functions, and all of them accept a list of strings as arguments and return a string (except for tawa() and niLaTawa().) To call a function, write it's name and then a pair of paranthesis with any arguments inside them.

Arguments to a function are delimited by spaces, but that's only neccesary if there are no other ways to separate them (for instance, string literals are fine.) Though it does look better if you put them anyways.

```ilo li sina
    tokiELinja("This is" " a string") # Ok. Says "This is a string."
    tokiElinja("This is"" a string") # Ok.
    a = "This is"
    tokiELinja(a " a string") # Ok.
    tokiELinja(a" a string") # Ok.
    b = " a string"
    tokiELinja(a b) # Ok.
    tokiELinja(ab) # Wrong. Not a and b, but ab, which isn't declared.
```

Function calls can also be nested to pass the result of a function as an argument to another:

```ilo li sina
    # Echoes what the user types.
    tokiELinja("You typed: " kamaJoTanJan()) 

    tokiELinja("Your name is: " kamaJoTanJan("What is your name?"))
```

Here are all of the functions:

#### **toki(\[messages...\]) -> nothing**

Prints the messages to the user.

#### **tokiELinja(\[messages...\]) -> nothing**

Like toki() but prints a newline afterward.

#### **kamaJoTanJan(\[messages...\]) -> user input**

Passes the messages to tokiELinja() and then gets input from the user and returns it. Blocks until input is received.

#### **wan(\[messages...\]) -> concatenated messages**

Concatenates the messages into a single string and returns it.

#### **tawa(label) -> nothing**

Jumps to the given label.

#### **niLaTawa(label yesMessage noMessage \[messages...\]) -> nothing**

Passes the messages to tokiELinja() along with the yes and no messages, and blocks until input is received from the user. If the user responds with the yes message, then it will jump to the given label. If the user responds with the no message then it will not jump and continue to the next line.

You can supply an empty string as either the yes or no message, but not both, as a wild card.

For example, if you put a wildcard for the yes message and "test" for the no message, then if the user types "test", it will not jump, but if they put anything else, it will.

If both the yes and no messages are not wildcards, and the user types anything other than those messages, then it will repeatedly ask until the user does.

#### **pokiPiLawaOS(\[names...\]) -> stored value or nothing**

Gets the value from a given enviroment variable.

The names are the possible variants for the desired variable. Each will be accessed one by one, returing the value of the first variable that has one. For example, the name of the user is usually stored in "USER" or "LOGNAME" on Linux distros, but in "USERNAME" on Windows. By supplying all 3 variants, you can ensure that it will work on both.

If none of the given variables have a value, then nothing is returned.

### ***Flow Control***

ilo li sina utilizes GOTOs (tawa() and niLaTawa()) for flow control.

The GOTOs require a label to jump to. A label can be created by typing the label name and placing a semicolon after it. Labels can only occur at the start of a line.

```ilo li sina
    tawa(Label)
    tokiELinja("This message will not be printed!")
Label:
```

In this example, tawa() jumps to Label, thus skipping the call to tokiELinja(), resulting in nothing being printed to the console.

tawa() always jumps, for conditional jumping you can use niLaTawa() instead.

```ilo li sina
Continue:
    tokiELinja("I'm continuing to say this!")
    niLaTawa(Continue "continue" "stop" \
             "Continue?")
    tokiELinja("I'm no longer continuing to say that ;(")
```

In this example, if the user says to continue, niLaTawa() will jump to Continue, forming a loop. Once the user says stop, the loop will be closed and the program will end.

### ***Variables***

You can use variables to store data for later. They are created by typing a name, the assignment operator '=', and an expression that is or returns a value. Their stored value can then be passed to functions or assigned to other variables.

```ilo li sina
    a = "test"
    b = a
    tokiELinja(b) # Says "test"

    a = kamaJoTanJan("What would you like?")
    tokiELinja("You cannot have " a) # If the user says "money" then "You cannot have money" will be printed.

    test = "test"    
Multiply:
    niLaTawa(Done "no" "yes"                      \
             "Do you want to multiply \"test\"?")
    test = wan(test test)
    tawa(Multiply)
Done:
    tokiELinja(test) # if the user chooses to multiply 4 times the output will be "testtesttesttesttesttesttesttesttesttesttesttesttesttesttesttest."
```

### ***Smaller Features***

#### *Escape characters:*

You can write special characters (such as a newline) within string literals using a backslash and the escaped character that corresponds to it.

 - \\n - Newline.
 - \\t - Tab.
 - \\v - Vertical tab.
 - \\b - Backspace.
 - \\" - Allows putting quotes into strings.
 - \\\\ - Allows putting backslashes into strings.

#### *Multiline statements:*

ilo li sina delimits statements usings newlines, meaning that statments start and end in a single line. However, you can place a backslash at the end of a line to carry a statement over to the next.

```ilo li sina
    abc   \
    =     \
    "yes"
    niLaTawa(Knows abc "no"                      \
             "Do you know the gingerbread man?")

    tokiELinja("This statement " " is" \
               " on several"           \
               " lines!")

    tawa(End)

Knows: tokiELinja(        \
                          \
                          \
                          \
                          \
                          \
                          \
                 "cool!")

End:
```

#### *EOF handling:*

kamaJoTanJan() and niLaTawa() force exit the program when they encounter an EOF character.

This is mainly due to the fact that the language is all IO. If there is nothing to read, there is nothing to do. Though, this does allow reading from files. For example, if you make and fill a file called "temp.txt" and run "temp.txt | ilo_li_sina \<program name\>", that ilo li sina program will pull input from that file until it hits the end, rather then forming an infinite loop.

#### *Preinitialized variables:*

There are a couple variables that come preinitialized and can be used in any ilo li sina program.

**__nanpa_Ilo_Li_Sina** - version number of the interpreter.

**__nimi_Ilo_Li_Sina** - name and path used to call the interpreter.

**__nimi_lipu** - name and path used to call the current program.

**__nimi_jan** - name of the user, acquired using pokiPiLawaOS("USER" "USERNAME" "LOGNAME"). If the user's name is not found then an empty string will be supplied.

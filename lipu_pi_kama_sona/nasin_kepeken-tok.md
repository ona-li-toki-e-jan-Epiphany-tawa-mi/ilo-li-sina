lukin kepeken toki ante: [English](nasin_kepeken-en_US.md "View in English")

# **nasin kepeken pi toki "ilo li sina"**

"ilo li sina" li toki pi lawa e ilo nanpa li lili li tawa taso kama jo en toki e nimi. taso, kepeken ni taso la sina ken pali e ijo mute.

ali lon toki ni li nimi. sina ken kepeken e nimi taso. sina ken pali e nimi lon lipu wawa kepeken sitelen '"' pi poki nimi (sama "test" en "ni li nimi")

## **ijo pi toki ni**

---------------

### ***nimi wawa***

"ilo li sina" li jo e nimi wawa lili. ona li kama jo e ijo li pali e ijo (taso, nimi wawa tawa() en niLaTawa() li ante). tawa pali la sina sitelen e nimi e poki tawa ijo "(" en ")" e ijo lon ona.

ijo tawa nimi wawa li kipisi kepeken sitelen " " pi lukin ala. ni li wile ala tawa ijo ante sama poki nanpa en nimi. taso, ni li lukin pona. pana la:

```ilo li sina
    tokiELinja("ni li" " nimi") # pona. li toki e "ni li nimi".
    tokiElinja("ni li"" nimi") # pona.
    a = "ni li"
    tokiELinja(a " nimi") # pona.
    tokiELinja(a" nimi") # pona.
    b = " nimi"
    tokiELinja(a b) # pona.
    tokiELinja(ab) # ike. poki "ab" li jo e ala li ni ala: "a" en "b".
```

sina ken pana e nimi wawa tawa nimi ante:

```ilo li sina
    # li toki e nimi jan.
    tokiELinja("sina toki e ni: " kamaJoTanJan()) 

    tokiELinja("sina jan " kamaJoTanJan("nimi sina li seme?"))
```

ona ale li ni:

#### **toki(\[nimi...\]) -> ala**

li toki e nimi tawa jan.

#### **tokiELinja(\[nimi...\]) -> ala**

sama toki() la li toki e nimi. taso, pini la ona li toki e linja sin.

#### **kamaJoTanJan(\[nimi...\]) -> nimi tan jan**

li pana e nimi tawa tokiELinja() li kama jo e nimi tan jan. li awen e lipu wawa. jan li toki e nimi la li open e lipu wawa.

#### **wan(\[nimi...\]) -> nimi wan tan nimi pana**

li wan e nimi lon nimi wan. 

#### **tawa(nimiTawa) -> ala**

li tawa lon nimi tawa.

#### **niLaTawa(nimiTawa nimiLon nimiPiLonAla \[nimiTawaToki...\]) -> ala**

li toki e nimi tawa toki e nimi lon e nimi pi lon ala e linja sin. jan li toki e nimi lon la li tawa lon nimi tawa. jan li toki e nimi pi lon ala la li tawa ala.

sina ken pana e nimi lon ala "" anu nimi ala pi lon ala. ni la nimi ali pi nimi ante ala li ken tawa ona. taso, ona tu li ken ala jo e ala lon tenpo sama.

pana la sina pana e "" tawa nimi lon e "test" tawa ante la jan li toki e "test" la ona li tawa ala. taso, jan li toki e nimi sama ala "test" la ona li tawa.

nimi lon en nimi pi lon ala li jo ala e ala la jan li toki ala e ona li toki e nimi ante la nimi niLaTawa() li toki sin e nimi tawa toki e nimi lon e nimi pi lon ala e linja sin.

#### **pokiPiLawaOS(\[nimiKen...\]) -> nimi lon poki nanpa anu ala**

li kama jo e nimi lon poki nanpa Enviroment Variables pi lawa OS pi nimi ken pi nanpa 1 pi jo e nimi.

lawa OS (sama Windows en Linux) li jo e poki nanpa Enviroment Variables lon poki Enviroment. lipu wawa ali li ken lukin e ona. sina ken kama jo e nimi lon poki ni kepeken nimi wawa ni.

nimi ken li nimi ali tawa poki nanpa wile. pana la nimi jan li ken lon "USER" anu "USERNAME" anu "LOGNAME" anu ante. taso, ona li lon ala ona ali. ni la sina ken pana e ona ali lon pokiPiLawaOS() li kama jo e nimi lon poki pi nanpa 1 pi jo e nimi.

poki nanpa li lon ala la li pana e ala.

### ***tawa***

toki li kepeken e nimi wawa GOTO (tawa() en niLaTawa()) tawa tawa lon lipu wawa.

nimi wawa ni li wile e nimi tawa tawa ni: ona li ken tawa lon ona. sina ken pali e ona kepeken nimi en sitelen ':' lon monsi. ona li ken lon open linja taso. pana la:

```ilo li sina
    tawa(nimiTawa)
    tokiELinja("mi toki ala e nimi ni!")
nimiTawa:
```

nimi tawa() li tawa lon "nimiTawa:". tan ni la nimi tokiELinja() li toki ala.

sina ken kepeken e nimi niLaTawa() sama ni tawa tawa ken. pana la:

```ilo li sina
awen:
    tokiELinja("mi awen toki e nimi ni!")
    niLaTawa(awen "pini ala" "pini" \
             "pini anu pini ala?")
    tokiELinja("mi awen ala toki e nimi ni ;(")
```

jan li toki e nimi "pini ala" la nimi niLaTawa() li tawa lon nimi tawa "awen". en, li awen toki e nimi. taso, jan li toki e "pini" la nimi niLaTawa() li tawa ala. en, li awen ala toki li pini.

### ***poki nanpa***

sina ken kepeken e poki nanpa tawa poki e nimi. sina ken pali e ona kepeken nimi en sitelen '=' en ijo tawa poki. sina ken pana e ona lon nimi wawa anu poki ante kepeken nimi ona. pana la:

```ilo li sina
    a = "test"
    b = a
    tokiELinja(b) # li toki e "test"

    a = kamaJoTanJan("sina wile e seme?")
    tokiELinja(a " li tawa ala sina") # nimi jan li "mani" la li toki e "mani li tawa ala sina".

    ijo = "ijo"
mute:
    niLaTawa(muteAla "mute ala" "mute"       \
             "li wile mute ala mute e ijo?")
    ijo = wan(ijo ijo)
    tawa(mute)
muteAla:
    tokiELinja(ijo) # jan li toki e mute lon tenpo 4 la li toki e "ijoijoijoijoijoijoijoijoijoijoijoijoijoijoijoijo".
```

### ***ijo lili***

#### *sitelen nasa:*

sina ken sitelen e sitelen nasa (sama linja sin) kepeken sitelen '\\'. ni li ona:

 - \\n - linja sin.
 - \\t - sitelen suli pi lukin ala.
 - \\v - sama \\t. taso, ona li tawa lon anpa.
 - \\b - li weka e sitelen 1.
 - \\" - li ken e ni: sina sitelen e sitelen '"' lon poki nimi.
 - \\\\ - li ken e ni: sina sitelen e sitelen '\\' lon poki nimi.

#### *ijo lon linja mute:*

"ilo li sina" la linja li kipisi e nimi wawa e pana lon poki nanpa e nimi tawa. taso, sina ken sitelen e ona lon linja mute kepeken sitelen '\\'. sina pana e ona lon pini linja la li awen lukin e linja lon anpa. pana la:

```ilo li sina
    abc    \
    =      \
    "sona"
    niLaTawa(liSona abc "sona ala"                     \
            "sina sona ala sona e jan pi pan namako?")

    tokiELinja("toki ni " " li" \
               " lon linja"     \
               " mute a!")

    tawa(pini)

liSona: tokiELinja(       \
                          \
                          \
                          \
                          \
                          \
                          \
                 "pona!")

pini:
```

#### *kama jo pi sitelen EOF (pini lipu):*

nimi wawa kamaJoTanJan() en niLaTawa() li kama jo e sitelen EOF la li pini e lipu wawa. 

ni li tan ni: ali pi toki ni li kama jo e nimi li toki e nimi. nimi li lon ala tawa kama la "ilo li sina" li ken pali e ala. taso, ona li ken e ni: kama jo e nimi tan lipu. pana la sina ken pana e nimi wile lon lipu "temp.txt" li sitelen e "temp.txt | ilo_li_sina \<nimi pi lipu wawa\>". lipu wawa li kama jo e nimi ali tan "temp.txt" la li pini li awen ala lon tenpo ali.

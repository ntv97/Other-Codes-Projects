def uniprot():
    import re
    diction = {}
    string = ">tr|A0A001|A0A001_STRVD MoeD5 OS=Streptomyces viridosporus OX=67581 GN=moeD5 PE=4 SV=1"
    newstr = string.replace("|", "`")
    pos = re.finditer("`",newstr)
    dbid = []
    for i in pos:
        dbid.append(i.span()[0])
    
    diction["db"] = string[1:dbid[0]]
    diction["Id"] = string[dbid[0]+1:dbid[1]]
    prot_end = re.search(" ", newstr)
    diction["Entry Protein"] = string[dbid[1]+1:prot_end.span()[0]]
    OSbeg = re.search("OS", newstr)
    OSend = re.search("OX", newstr)
    diction["OS"] = string[OSbeg.span()[0]+3:OSend.span()[0]-1]
    GNbeg = re.search("GN", newstr)
    PEbeg = re.search("PE", newstr)
    if GNbeg.span()[0] != -1:
        diction["GN"] = string[GNbeg.span()[0]+3:PEbeg.span()[0]-1]
    SVbeg = re.search("SV", newstr)
    diction["PE"] = string[PEbeg.span()[0]+3:SVbeg.span()[0]-1]
    diction["SV"] = string[SVbeg.span()[0]+3:]
    
    for elements in diction:
        print(elements, ": ", diction[elements])

uniprot()

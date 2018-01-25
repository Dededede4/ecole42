
def my_var():
    a = 42
    b = "42"
    c = "quarante-deux"
    d = 42.0
    e = True
    f = [42]
    g = {42:42}
    h = (42,);
    i = set()
    print("%s est de type %s" % (a, type(a)));
    print("%s est de type %s" % (b, type(b)));
    print("%s est de type %s" % (c, type(c)));
    print("%s est de type %s" % (d, type(d)));
    print("%s est de type %s" % (e, type(e)));
    print("%s est de type %s" % (f, type(f)));
    print("%s est de type %s" % (g, type(g)));
    print("%s est de type %s" % (h, type(h)));
    print("%s est de type %s" % (i, type(i)));

if __name__ == '__main__':
    my_var()

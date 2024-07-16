import hashlib
import os

if __name__ == "__main__":
    os.system("./create_bmp_for_microstrip_coupler 1.5 2.0 1 1.593 0.035 1 3.7 out.bmp")
    md5 = hashlib.md5(open("out.bmp", "rb").read()).hexdigest()
    os.remove("out.bmp")
    assert(md5 == "3cbb4ffad5e447ae377c2a6982f163db")

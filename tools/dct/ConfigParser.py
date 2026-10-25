# py3 shim: MTK's DCT tools were written against the py2 module name.
#
# py2's ConfigParser tolerated duplicate options (last one wins); py3's default
# is strict=True which raises DuplicateOptionError. MT6853.fig has a duplicate
# gpio77 entry, so force strict=False to preserve py2 behaviour.
import configparser as _cp

class ConfigParser(_cp.ConfigParser):
    def __init__(self, *a, **kw):
        kw.setdefault('strict', False)
        super().__init__(*a, **kw)

class RawConfigParser(_cp.RawConfigParser):
    def __init__(self, *a, **kw):
        kw.setdefault('strict', False)
        super().__init__(*a, **kw)

class SafeConfigParser(ConfigParser):
    pass

NoSectionError = _cp.NoSectionError
NoOptionError = _cp.NoOptionError
Error = _cp.Error
DEFAULTSECT = _cp.DEFAULTSECT

from itertools import chain

#will be called from server/client script
def getServerList(args):
    base = ["boost-hana"]
    add = {"qt6.1.1": ["websocketpp"], "macos-latest": ["range-v3"]}
    return chain(base, *[add[arg] for arg in filter(lambda x: x in add, args)])

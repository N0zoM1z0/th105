# UDP request-buffer array ownership

Original Japanese TH105 v1.06a SHA-256:
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

The shared buffer at CNetworkUDP+78 is allocated as an unsigned-byte array by
the complete start-connection source 415340. Its native replacement cleanup at
4153E8 calls array delete 68AA26, followed by array allocation 665B8A at 4153FD.
The same deallocator is called from initialization 412F28, shutdown 41306E and
normal destruction 412D03. The pointer is retained as the allocation base.

Four source views now identify this actual byte-array pointer and pair it with
delete[] rather than free:

- NetworkWinsockReceiveThread.cpp: replacement during start_connection.
- NetworkWinsockRuntime.cpp: initialization cleanup.
- NetworkWinsockShutdown.cpp: shutdown cleanup.
- NetworkWinsockConstructorRuntime.cpp: normal owner destruction.

The real <new> declaration is present before delete[]. This avoids VC8's
undeclared-array-operator fallback. Existing source guards, assignments,
wire lengths and thread/callback ordering are unchanged. Scoped call bindings
identify the actual array delete symbol; scalar STL node/allocation deletion
is not remapped or changed.

## Focused verification

All five actual source-consuming units compile. The four units with accepted
authored functions freshly replay eight old matches: shutdown 175, receive-thread
entry, four Winsock runtime/bind helpers, packet manager destructor 98 and packet
manager constructor 145 with its complete EH proof. The packet manager's existing
30-byte scalar wrapper also freshly compares exact, for nine full comparisons.

The unaccepted scalar-owner candidate compiles but earns no credit. Current
linked owner construction still emits 357 bytes and normal destruction 341/native333;
neither becomes accepted from the ownership correction.

The changed source set and pre-edit copies are retained privately for
reproducibility. No unrelated native units or whole origin census were
cold-replayed.

All reconstruction totals remain unchanged:1565 exact /446423 bytes,
source 1761/authored1781/mapped1788, excluded 1658/review588, units 753.

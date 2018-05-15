#!/bin/bash
BOB_START=$(./bshell --bpaceBobStart -password qwer -l 128)
echo $'Bob first:\n'${BOB_START}
TO_ALICE=$(echo "${BOB_START}" | cut -d ':' -f 2 | cut -d ' ' -f 2)
ALICE_START=$(./bshell --bpaceAliceStart -password qwer -l 128 -in ${TO_ALICE})
echo $'Alice first:\n'${ALICE_START}
TO_BOB=$(echo "${ALICE_START}" | cut -d ':' -f 2 | cut -d ' ' -f 2)
BOB_SECOND=$(./bshell --bpaceBobSecond -password qwer -in ${TO_BOB})
echo $'Bob second:\n'${BOB_SECOND}
TO_ALICE_SECOND=$(echo "${BOB_SECOND}" | cut -d ':' -f 2 | cut -d ' ' -f 2)
echo $'Alice second:'
./bshell --bpaceAliceSecond -password qwer -in ${TO_ALICE_SECOND}

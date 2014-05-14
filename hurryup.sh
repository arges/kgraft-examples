#!/bin/bash
for p in $(ls /proc/ | grep '^[0-9]'); do
  if [[ -e /proc/$p/kgr_in_progress ]]; then
    if [[ `sudo cat /proc/$p/kgr_in_progress` -eq 1 ]]; then
     echo $p;
     sudo kill -SIGCONT $p
    fi
  fi
done

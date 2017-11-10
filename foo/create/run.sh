#!/bin/bash
(for i in `seq 100`; do ./create; done;) | uniq 2>&1 | tee run.log

#!/bin/bash

find . -type f -name \*.sh -exec basename {} .sh ';' 2>/dev/null

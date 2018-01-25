#!/bin/bash
curl -v $1 2>&1 | grep "< Location:" | cut -c13-

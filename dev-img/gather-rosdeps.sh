#!/bin/bash
set -euxo pipefail

colcon list --packages-up-to ${PACKAGE} -p | awk 'ORS=" "' > /tmp/packages-list
rosdep install \
    --from-paths $(cat /tmp/packages-list) \
    --ignore-src \
    --rosdistro "${ROSDISTRO}" \
    --skip-keys "libpcl-all-dev" \
    --reinstall \
    --simulate \
  > rosdep_output.sh

echo "apt-get install -y \\" > compressed_install.sh
cat rosdep_output.sh | awk '/^  apt-get install/' | awk '{print $3;}' | sort | awk 'NR > 1{print "  "line" \\"}{line=$0;}END{print "  "$0" "}' >> compressed_install.sh
chmod +x compressed_install.sh

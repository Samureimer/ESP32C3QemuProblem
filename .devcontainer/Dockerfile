FROM espressif/idf

ARG DEBIAN_FRONTEND=nointeractive
ARG CONTAINER_USER=esp
ARG USER_UID=1000
ARG USER_GID=$USER_UID

RUN apt-get update \
  && apt install -y -q \
  cmake \
  git \
  hwdata \
  libglib2.0-0 \
  libnuma1 \
  libpixman-1-0 \
  linux-tools-virtual \
  && rm -rf /var/lib/apt/lists/*

RUN update-alternatives --install /usr/local/bin/usbip usbip `ls /usr/lib/linux-tools/*/usbip | tail -n1` 20

#https://github.com/espressif/qemu/releases/download/esp-develop-8.0.0-20230522/esp-qemu-riscv32-softmmu-develop_8.0.0_20230522-x86_64-linux-gnu.tar.bz2
# QEMU
ENV QEMU_DIST=esp-qemu-riscv32-softmmu-develop_8.0.0_20230522-x86_64-linux-gnu.tar.bz2
ENV QEMU_URL=https://github.com/espressif/qemu/releases/download/esp-develop-8.0.0-20230522/esp-qemu-riscv32-softmmu-develop_8.0.0_20230522-x86_64-linux-gnu.tar.bz2

ENV LC_ALL=C.UTF-8
ENV LANG=C.UTF-8

RUN apt-get update \
  && apt install -y -q \
  libslirp0 \
  libslirp-dev

RUN wget --no-verbose ${QEMU_URL} \
  && tar -xf $QEMU_DIST -C /opt \
  && rm ${QEMU_DIST}

ENV PATH=/opt/qemu/bin:${PATH}

RUN groupadd --gid $USER_GID $CONTAINER_USER \
  && adduser --uid $USER_UID --gid $USER_GID --disabled-password --gecos "" ${CONTAINER_USER} \
  && usermod -a -G dialout $CONTAINER_USER
USER ${CONTAINER_USER}
ENV USER=${CONTAINER_USER}
WORKDIR /home/${CONTAINER_USER}

RUN echo "source /opt/esp/idf/export.sh > /dev/null 2>&1" >> ~/.bashrc

#ENTRYPOINT [ "/opt/esp/entrypoint.sh" ]

CMD ["/bin/bash", "-c"]
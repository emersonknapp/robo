# Robobrains

## Udev rules

Install them all from `udev/`

## Process control

Copy `systemd/` services to `~/`

Copy `docker-compose.yml` to `~/`


## Docker registry setup

Add the following to registry host (dev computer)

```
# /etc/docker/daemon.json
"insecure-registries": ["0.0.0.0:5000"]
```

Run the registry

```
docker run -d -p 5000:5000 --restart=always --name registry registry:2
```

Add the following to robot

```
# /etc/docker/daemon.json
"insecure-registries": ["XXX.XXX.X.XX:5000"]
```

## Deployment

Host upload

```
docker tag emerson/aarch64-ubuntu-eloquent kojet-runtime
docker push localhost:5000/kojet-runtime
rsync -v -r install_aarch64/ robot:~/install_aarch64
```

Robot download

```
docker pull localhost:5000/kojet-runtime
systemctl --user enable robot-runtime
systemctl start robot-runtime
```

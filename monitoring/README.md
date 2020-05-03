# Monitoring

Prometheus server - download release binary
https://github.com/prometheus/prometheus/releases

Node exporter - download release binary
https://github.com/prometheus/node_exporter/releases

```
docker run -p 3000:3000 grafana/grafana
```


CPU query

```
1 - (avg by (instance) (irate(node_cpu_seconds_total{job="node",mode="idle"}[5m])))
```

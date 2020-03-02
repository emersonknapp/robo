module spacer(inner, thickness, height) {
    difference() {
        cylinder(height, inner+thickness, inner+thickness, $fn=50);
        cylinder(height, inner, inner, $fn=50);
    }
}

spacer(1.7, 1.5, 2.5);
    
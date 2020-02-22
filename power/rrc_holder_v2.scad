//cube(10, 10, 10);

eps = 0.5;

module battery() {
    length = 85.1;
    width = 77.4;
    height = 22.4;
    radius = height / 2.0;
    
    translate([0, radius, radius])
    rotate([0, 90, 0])
        hull() {
            cylinder(length, radius, radius, $fn=100);
            translate([0, width - height, 0]) cylinder(length, radius, radius, $fn=100);
        }
    buff = 7;
    diff = 15;
    translate([0, 0, -10]) {
    translate([buff, radius, 0]) cube([10, width - height, 40]);
    translate([buff+diff*1, radius, 0]) cube([10, width - height, 40]);
    translate([buff+diff*2, radius, 0]) cube([10, width - height, 40]);
    translate([buff+diff*3, radius, 0]) cube([10, width - height, 40]);
    translate([buff+diff*4, radius, 0]) cube([10, width - height, 40]);
    }
}

module pmm() {
    width = 50.0;
    length = 60.0;
    height = 15.0;
    cube([width, length, height]);
    translate([-3, 0, 0]) cube([4, length, height+2]);
    translate([0, length, 0]) cube([width, 20, height+2]);
    translate([4, 4, -10]) {
        cylinder(30, 1.65, 1.65);
        translate([0, 44, 0]) cylinder(30, 1.64, 1.65);
        translate([41, 0, 0]) {
            cylinder(30, 1.65, 1.65);
            translate([0, 52, 0]) cylinder(30, 1.65, 1.65);
        }
    }
}

module baseblock() {
    over = 0;
    base_height = 10;
    block_length = length + pmm_length + 2;
    block_width = 78;
    translate([-over, -over, -over]) 
        cube([block_width, base_height, block_length]);
}


over = 2;
difference() {    
    cube([85.1+50+2+over, 77.4+over, 5]);
    translate([1, 1, 0.2]) {
    translate([0, 0, 0]) battery();
    translate([85.1+2, 0, 0]) pmm();
}
}

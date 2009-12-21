import Qt 4.6

Image {
    function accessor(x) {print("not implemented");return null;}
    x: accessor("_x")
    y: accessor("_y")
    source: "../" + accessor("")
}

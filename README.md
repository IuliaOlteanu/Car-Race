**Car Race**
##
The assignment required a partial implementation of a car racing game. It was necessary to create the race track, the car control on the track, a set of dynamic obstacles that will have a predefined path on the track and substitute the opposing cars that the race is made against, and a curve effect of the track from the car's position.

**Race Track**

To generate a track on which the car will move, we initially need a set of points that define it. The set consists of points in the XOZ plane (2D).

The track must meet 2 conditions:
\
➢ There must be no right angle between any two consecutive segments.
\
➢ It must be a concave polygon.

**Track geometry generation**

Generating the race track can be done according to the following steps:

     ➢ Create the points of a polygon that defines the race track.
     ➢ Create two sets of additional points, inside and outside the polygon that defines the track. The points can be created along the perpendicular of each segment.
     ➢ Create the edges between the points of the interior and exterior polygon.
     ➢ Generate the triangles between the points of the two polygons. The triangles are created in a single mesh object.

To generate the geometry of the track (a 2D surface), we need 2 sets of points: one interior and one exterior. Each exterior segment is (approximately) parallel to its interior counterpart. From a set of points, we can generate as many sets of points parallel to the initial set (parallelism at the segment level) as we need.

<img width="412" alt="image" src="https://user-images.githubusercontent.com/73997287/220973817-608d523c-6f55-4429-bf34-0cf41c7bb8f2.png">

With the two sets (interior and exterior), we can build the track surface. Let's assume that we have the outer points r1, r2, r3, and the inner points a1, a2, a3. The four triangles (r1, a1, a2), (r1, a2, r2), (r2, a2, a3), (r2, a3, r3) must be constructed.

Thus, if we apply the same thing for all the points in both sets, we get the track.

**Moving dynamic obstacles**

On the track, besides the player's car, other cars (opponents) must move on a predefined path parallel to the set of points that generate the track. This path can be obtained with the technique presented above.

**Generating trees next to the track**

In addition to the track, decorative trees are located. At least one tree must be constantly visible on the screen (requires high tree density). Trees should not block the track.

**Car Control**

Of all the cars created on the track, one of them is the player's car. It can be controlled using the W, A, S, D keys, where W-S represents the forward-backward movement, and A-D will change the orientation of the car.

**Camera control**

The player's perspective will be a third-person one, so the camera is positioned behind the car, looking at it. For the smoothest control, the car will remain centered on the camera direction, so when the A-D keys are pressed, both the car and the camera will rotate. Moving forward-backward (W-S) will involve moving the car according to the camera's rotation.

** Checking if the car is on the track**

For this, we use the Triangle Area algorithm, which is described here: https://www.baeldung.com/cs/check-if-point-is-in-2d-triangle.

**Dynamic obstacle collision checking**

In order to have interaction with enemy vehicles, we need to detect them. This detection involves checking the position of the player's vehicle in relation to each enemy vehicle. To do this, a sphere-sphere collision check is performed.

Sphere-Sphere collision: https://developer.mozilla.org/enUS/docs/Games/Techniques/3D_collision_detection

The spheres would have their centers at the center of the vehicle, and the radius of the sphere represents the collision detection distance.

When an intersection between the player's vehicle and a dynamic obstacle is detected, the player's vehicle must stop. Any key pressed for movement or rotation control should no longer change the position or orientation of the vehicle. This stopping effect disappears when there is no longer an intersection.

**Minimap**

A minimap is rendered in one of the corners of the screen. To view the scene from above, the following is done:

     ➢ The camera position is moved above the vehicle (and consequently, the center of the camera's position);
     ➢ he camera is switched to an orthographic projection.

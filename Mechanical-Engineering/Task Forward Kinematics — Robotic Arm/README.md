# Forward Kinematics — Robotic Arm (4 DOF)

## Objective
The robotic arm in the provided image contains four motors (4 DOF). The objective is to write the Forward Kinematics equations to find the spatial coordinates (x, y, z) for the arm's movement based on the given dimensions.

**Given Dimensions from the Reference Image:**
* Base height — 15 mm
* Upper arm — 65 mm
* Forearm — 100 mm

---

## 1. Overview
This document derives the Forward Kinematics equations for a 4-degree-of-freedom (4-DOF) robotic arm. It consists of a rotating base and three consecutive joints (shoulder, elbow, wrist). The goal is to calculate the end-effector position (x, y, z) as a function of the four joint angles (θ1, θ2, θ3, θ4).

## 2. Given Parameters

| Link | Description | Length |
| :--- | :--- | :--- |
| L0 | Base height | 15 mm |
| L1 | Upper arm | 65 mm |
| L2 | Forearm | 100 mm |
| L3 | Wrist-to-gripper (assumed) | 20 mm |

**Joint Angles:**
* **θ1** → Base rotation (around Y-axis)
* **θ2** → Shoulder joint
* **θ3** → Elbow joint
* **θ4** → Wrist joint

## 3. Assumptions
* The base rotates around the Y-axis, meaning the horizontal plane of movement is X-Z, and the Y-axis represents elevation/height.
* All angles are measured from the horizontal and are positive in the counter-clockwise direction.
* The angles θ2, θ3, and θ4 are cumulative — each angle is measured relative to the orientation of the preceding link.
* The length of the link from the wrist to the gripper is not specified in the reference image. Therefore, we assumed L3 = 20 mm as a reasonable estimate to allow all four motors to contribute to the final end-effector position.
* At θ1 = θ2 = θ3 = θ4 = 0°, the arm is fully extended along the X-axis.

## 4. Derivation

**Step 1 — Planar Projection (Ignoring base rotation)**
Treating the arm as a 2D planar mechanism, the horizontal reach (r) and the vertical height relative to the base are:

```text
r  = L1·cos(θ2) + L2·cos(θ2+θ3) + L3·cos(θ2+θ3+θ4)
Δy = L1·sin(θ2) + L2·sin(θ2+θ3) + L3·sin(θ2+θ3+θ4)
```

**Step 2 — Adding Constant Base Height**
```text
y = L0 + Δy
```

**Step 3 — Applying Base Rotation around Y**
Since the base rotates around Y, the reach `r` is distributed between the X and Z axes (using polar coordinates):
```text
x = r · cos(θ1)
z = r · sin(θ1)
```

## 5. Final Forward Kinematics Equations

```text
x = [L1·cos(θ2) + L2·cos(θ2+θ3) + L3·cos(θ2+θ3+θ4)] · cos(θ1)
z = [L1·cos(θ2) + L2·cos(θ2+θ3) + L3·cos(θ2+θ3+θ4)] · sin(θ1)
y = L0 + L1·sin(θ2) + L2·sin(θ2+θ3) + L3·sin(θ2+θ3+θ4)
```
**Where:** L0 = 15 mm, L1 = 65 mm, L2 = 100 mm, L3 = 20 mm (assumed)

## 6. Notes
* All four motors contribute directly to the end-effector's position (x, y, z), as θ4 is modeled as an in-plane joint with an assumed link length (L3), rather than a pure roll joint.
* This assumption was made because the reference drawing does not specify a length for the wrist-to-gripper link.

## 7. Numerical Verification (MATLAB)
To verify the accuracy of the equations, a simple MATLAB Online script was written to calculate (x, y, z) based on the final equations above.

 **[Click here to view the full MATLAB code](code)**

**Result at θ1 = θ2 = θ3 = θ4 = 0°:**

![MATLAB Output Result](image.png)

```text
x = 185.00 mm
y = 15.00 mm
z = 0.00 mm
```

This perfectly matches the theoretical expectation: when all angles are zeroed out, the arm is fully extended along the X-axis with a length of (L1 + L2 + L3 = 185 mm), while Y equals only the base height (L0 = 15 mm). 

This numerical verification confirms that the manually derived equations are correct and applied consistently.

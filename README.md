# About
This project uses an Arduino (UNO R4 WiFi), a servo motor (MG996R), and Tailscale to activate my gate and garage remotes securely over the internet using my iPhone &mdash; either through voice command (Siri) or at the press of a button.
<img src="./docs/demo.gif" width="100%"/>

# How it works
<img src="./docs/open-gate-workflow.svg" alt="A GIF demonstrating the usage" width="100%"/>

### Arduino server and servo motor
The angle of the servo motor's arm is controlled by the Arduino. The Arduino hosts a simple HTTP server on my home network. HTTP GET requests to `http://<arduino-server-ip>/gate` and `http://<arduino-server-ip>/garage` cause the Arduino to rotate the servo motor's arm just enough to physically activate the corresponding remote. A wooden mount is used to secure and align the servo motor and remotes. The Arduino and wooden mount assembly are placed within range for the gate and garage to be activated by their corresponding remote.

### Tailscale and proxy server
> "A Tailscale network (known as a tailnet) is a secure, interconnected collection of users, devices, and resources. Your tailnet is your private space, inaccessible from the public internet. It's akin to a secure conference room where only invited participants can enter."
> - Tailscale Docs

Since the Arduino server is connected to my home Wi-Fi, it can only receive requests from devices within my home network (i.e., connected to my home Wi-Fi). To enable secure requests from my phone when it's on a different network (e.g., phone is using mobile data), I use Tailscale. Both my phone and laptop connect to the same Tailscale network, allowing for secure communication between them across different networks. My laptop is also connected to my home network, allowing it to act as an intermediary between my Tailscale network and home network. A proxy server running on my laptop forwards requests received from my phone to the Arduino server.

### Apple Shortcuts
Apple Shortcuts provides the `Get Contents of URL` shortcut action, which sends an HTTP GET request to a target URL. Using `Get Contents of URL`, I've created four shortcuts appropriately named "Open the gate", "Close the gate", "Open the garage", and "Close the garage", to target `http://<proxy-server-ip>/gate` and `http://<proxy-server-ip>/garage`. For example, "Open the gate" uses `Get Contents of URL` to send an HTTP GET request to `http://<proxy-server-ip>/gate`. Note that "Open the gate/garage" and "Close the gate/garage" do the same thing &mdash; they activate the remote. These shortcuts can be activated from the Shortcuts app, the Home screen (must be added first), or through voice command using Siri. For example, "Hey Siri, close the garage." will execute the "Close the garage" shortcut.

# What's next?
* Host the proxy server on a Raspberry Pi. Currently, I'm using my laptop to host the proxy server, which isn't ideal since it isn't always on or connected to my home network. In either case, there would be no way to reach the Arduino server from a different network.
* Replace the wooden mount that holds the servo motor and remotes with a more refined and visually appealing 3D-printed mount.

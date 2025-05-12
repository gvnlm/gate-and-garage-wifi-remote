# About
This project uses an Arduino (UNO R4 WiFi), a servo motor (MG996R), and Tailscale to allow me to activate my gate and garage remotes securely over the internet. Activation is done via my iPhone using Apple Shortcuts — either through voice command (Siri) or at the press of a button.
<img src="./docs/demo.gif" width="100%"/>

# How it works
<img src="./docs/open-gate-workflow.svg" width="100%"/>

### Arduino server and servo motor
The angle of the servo motor arm is controlled by the Arduino. The Arduino hosts a simple HTTP server on my home network. HTTP GET requests to `http://<arduino-server-ip>/gate` and `http://<arduino-server-ip>/garage` cause the Arduino to rotate the servo motor arm just enough to physically activate the respective remote. A wooden mount is used to secure and align the servo motor and remotes. The Arduino and wooden mount assembly are placed within range for the gate and garage to be activated by their respective remote.

### Tailscale and proxy server
> "A Tailscale network (known as a tailnet) is a secure, interconnected collection of users, devices, and resources. Your tailnet is your private space, inaccessible from the public internet. It's akin to a secure conference room where only invited participants can enter."
> - [Tailscale Docs](https://tailscale.com/kb/1136/tailnet)

Since the Arduino server is connected to my home Wi-Fi, it can only receive requests from devices within my home network (i.e., connected to my home Wi-Fi). To enable secure requests from my phone when it's on a different network (e.g., phone is using mobile data), I use Tailscale. Both my phone and laptop connect to the same Tailscale network, allowing for secure communication between them across different networks. My laptop is also connected to my home network, allowing it to act as an intermediary between my Tailscale network and home network. A proxy server running on my laptop forwards requests received from my phone to the Arduino server.

### Apple Shortcuts
Apple Shortcuts provides the `Get Contents of URL` shortcut, which sends an HTTP GET request to a target URL.

# What's next?
* Host the proxy server on a Rasberry Pi. Currently, I'm using my laptop to host the proxy server, which isn't ideal since it isn't always on or connected to my home network. In either case, there would be no to way to reach the Arduino server from a different network.
* Replace the wooden mount that holds the servo motor and remotes with a more refined (and visually appealing) 3d-printed mount.

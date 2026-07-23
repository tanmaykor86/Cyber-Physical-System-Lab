from flask import Flask

app = Flask(__name__)

@app.route("/")
def home():

    try:
        with open("gesture.txt", "r") as f:
            gesture = f.read().strip()
    except:
        gesture = "Waiting..."

    return f"""
    <!DOCTYPE html>
    <html>
    <head>
        <title>Gesture Detection</title>
        <meta http-equiv="refresh" content="1">
        <style>
            body {{
                font-family: Arial;
                text-align: center;
                margin-top: 100px;
                background: #f5f5f5;
            }}

            h1 {{
                font-size: 50px;
            }}

            h2 {{
                font-size: 80px;
                color: blue;
            }}
        </style>
    </head>

    <body>
        <h1>Detected Gesture</h1>
        <h2>{gesture}</h2>
    </body>
    </html>
    """

if __name__ == "__main__":
    app.run()
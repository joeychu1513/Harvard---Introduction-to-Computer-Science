import os
import datetime

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    user_id = session["user_id"]

    total_value, stocks_combined, remaining_cash = get_current_situation(user_id)

    # stocks_combined = [{"symbol": "aaaa", "stock_name": "aaab", "shares": 5, "price": 11, "total": 222.333}, {"symbol": "baaa", "stock_name": "baab", "shares": 2, "price": 21, "total": 522}]
    return render_template("index.html", cash=remaining_cash, stocks=stocks_combined, total=total_value)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""


    if request.method == "POST":
        symbol = request.form.get("symbol")
        try:
            shares = float(request.form.get("shares"))
        except:
            return apology("shares not positive integer", 400)

        info = lookup(symbol)

        # input check
        if info is None:
            return apology("invalid symbol", 400)
        if shares % 1 != 0:
            return apology("shares not positive integer", 400)
        if shares <= 0:
            return apology("shares not positive integer", 400)

        # sql process

        user_id = session["user_id"]
        cash_dict = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        cash = cash_dict[0]["cash"]

        stock_name=info["name"]
        stock_price=info["price"]
        stock_symbol=info["symbol"]

        timenow = datetime.datetime.now().isoformat()

        # check if enough cash

        if cash < stock_price * shares:
            return apology("not enough cash", 400)

        # deduct cash from user, after buy

        remaining_cash = cash - stock_price * shares
        to_add_user = db.execute("UPDATE users SET cash = ? WHERE id = ?", remaining_cash, user_id)
        if to_add_user is None:
            return apology("unknown error to_add_user", 400)

        # add to transaction table

        to_add_transaction = db.execute("INSERT INTO transactions (user_id, symbol, price, time, stock, shares) VALUES(?, ?, ?, ?, ?, ?)", user_id, stock_symbol, stock_price, timenow, stock_name, shares)
        if to_add_transaction is None:
            return apology("unknown error to_add_transaction", 400)
        return redirect("/")


    # if GET method
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    user_id = session["user_id"]
    # total_value, stocks_combined, remaining_cash = get_current_situation(user_id)

    # get history

    transactions = db.execute("SELECT * FROM transactions WHERE user_id = ?", user_id)

    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # check if this is POST method
    if request.method == "POST":
        symbol = request.form.get("symbol")
        info = lookup(symbol)

        if info is None:
            return apology("invalid symbol", 400)
        else:
            return render_template("quoted.html", stock_name=info["name"], stock_price=info["price"], stock_symbol=info["symbol"])

    # if GET method
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # check if this is POST method
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # check if username is not empty
        if len(username) == 0:
            return apology("empty username", 400)

        # check if username exist
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)
        if len(rows) > 0:
            return apology("username has already existed", 400)

        # check if password is not empty
        if len(password) == 0 or len(confirmation) == 0:
            return apology("empty password", 400)

        # check if password not match
        if password != confirmation:
            return apology("password not match", 400)


        # convert password to hash
        hash = generate_password_hash(password)

        # pass the checking and going to store

        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, hash)
        return redirect("/login")

    # if GET method
    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # get owning stocks

    user_id = session["user_id"]
    total_value, stocks_combined, remaining_cash = get_current_situation(user_id)

    # if post

    if request.method == "POST":

        # check input
        if not request.form.get("symbol"):
                return apology("missing symbol", 400)

        # check if own the stock
        # check if more than ownning stock

        to_sell_stock = request.form.get("symbol")
        to_sell_shares = float(request.form.get("shares"))
        to_sell_price = None
        to_sell_stock_name = None

        if to_sell_shares % 1 != 0:
            return apology("shares not positive integer", 400)
        if to_sell_shares <= 0:
            return apology("shares not positive integer", 400)

        for i, item in enumerate(stocks_combined):
            if item["symbol"] == to_sell_stock:
                if to_sell_shares <= item["shares"]:
                    to_sell_price = item["price"]
                    to_sell_stock_name = item["stock_name"]
                    break
                else:
                    return apology("not enough shares", 400)
            else:
                if i < len(stocks_combined) - 1:
                    continue
                else:
                    return apology("not owning the stock", 400)

        # update user(cash) and transaction and return to index.html

        to_add_transaction = db.execute("INSERT INTO transactions (user_id, symbol, price, time, stock, shares) VALUES(?, ?, ?, ?, ?, ?)", user_id, to_sell_stock, to_sell_price, datetime.datetime.now().isoformat(), to_sell_stock_name, -to_sell_shares)
        if to_add_transaction is None:
            return apology("unknown error to_add_transaction", 400)

        to_add_user = db.execute("UPDATE users SET cash = ? WHERE id = ?", remaining_cash + to_sell_price * to_sell_shares, user_id)
        if to_add_user is None:
            return apology("unknown error to_add_user", 400)

        return redirect("/")

    # if GET method
    else:
        return render_template("sell.html", stocks=stocks_combined)


def get_current_situation(user_id):

    remaining_cash_list = db.execute("SELECT * FROM users WHERE id = ?", user_id)

    if remaining_cash_list is None:
        return apology("remaining_cash_list", 400)
    remaining_cash = remaining_cash_list[0]["cash"]
    total_value = remaining_cash

    # getting the holding stock
    stocks_history_list = db.execute("SELECT * FROM transactions WHERE user_id = ?", user_id)

    # list of dictionary: symbol, stock_name, shares, price, total
    stocks_combined = []

    # combine the query result
    for stock_history in stocks_history_list:

        current_symbol = stock_history["symbol"]
        current_price = lookup(current_symbol)["price"]

        if len(stocks_combined) == 0:
            stocks_combined.append({"symbol": stock_history["symbol"], "stock_name": stock_history["stock"], "shares": stock_history["shares"], "price": current_price, "total": current_price * stock_history["shares"]})
            total_value += stock_history["shares"] * current_price

        else:
            for j, stock_combined in enumerate(stocks_combined):

                if stock_combined["symbol"] == stock_history["symbol"]:
                    stock_combined["shares"] += stock_history["shares"]
                    stock_combined["total"] = stock_combined["shares"] * current_price
                    total_value += stock_history["shares"] * current_price
                    break
                else:
                    if j < len(stocks_combined) - 1:
                        continue
                    else:
                        stocks_combined.append({"symbol": stock_history["symbol"], "stock_name": stock_history["stock"], "shares": stock_history["shares"], "price": current_price, "total": current_price * stock_history["shares"]})
                        total_value += stock_history["shares"] * current_price
                        break

    return total_value, stocks_combined, remaining_cash
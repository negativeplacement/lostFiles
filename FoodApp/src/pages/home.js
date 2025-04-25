import React, {useState, useEffect} from 'react';
import {Offcanvas, OffcanvasHeader, OffcanvasBody, Button, Card, ListGroup, ListGroupItem, ListGroupItemHeading, ListGroupItemText, ListInlineItem } from 'reactstrap';

const Home=()=>{
    const [toggle, setToggle] = useState(false);
    function buttonPushed(){
        setToggle(toggle => !toggle);
    }

    return (
        <div>
            <h1>Welcome to CookBook Pro</h1>
            <Button color="primary" onClick={() => buttonPushed()}>Open</Button>
            <Offcanvas backdrop={false} isOpen={toggle}>
                <OffcanvasHeader toggle={() => buttonPushed()}>Offcanvas</OffcanvasHeader>
                <OffcanvasBody><strong>This is the Offcanvas body.</strong></OffcanvasBody>
            </Offcanvas>
        </div>
    );
};

export default Home;